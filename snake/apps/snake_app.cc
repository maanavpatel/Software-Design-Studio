// Copyright (c) 2020 CS126SP20. All rights reserved.

#include "snake_app.h"

#include <cinder/Font.h>
#include <cinder/Text.h>
#include <cinder/Vector.h>
#include <cinder/gl/draw.h>
#include <cinder/gl/gl.h>
#include <gflags/gflags.h>
#include <snake/player.h>
#include <snake/segment.h>

#include <algorithm>
#include <chrono>
#include <cmath>
#include <random>
#include <string>

namespace snakeapp {

using cinder::Color;
using cinder::ColorA;
using cinder::Rectf;
using cinder::TextBox;
using cinder::app::KeyEvent;
using cinder::app::loadAsset;
using cinder::audio::load;
using snake::Direction;
using snake::Location;
using snake::Segment;
using std::string;
using std::chrono::duration_cast;
using std::chrono::seconds;
using std::chrono::system_clock;

const double kRate = 25;
const size_t kLimit = 3;
const char kDbPath[] = "snake.db";
const seconds kCountdownTime = seconds(10);
const Color kDefaultFoodColor = {.5, 1.0, .3};
#if defined(CINDER_COCOA_TOUCH)
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial-BoldMT";
const char kDifferentFont[] = "AmericanTypewriter";
#elif defined(CINDER_LINUX)
const char kNormalFont[] = "Arial Unicode MS";
const char kBoldFont[] = "Arial Unicode MS";
const char kDifferentFont[] = "Purisa";
#else
const char kNormalFont[] = "Arial";
const char kBoldFont[] = "Arial Bold";
const char kDifferentFont[] = "Papyrus";
auto start = std::chrono::high_resolution_clock::now();
#endif

DECLARE_uint32(size);
DECLARE_uint32(tilesize);
DECLARE_uint32(speed);
DECLARE_uint32(lives);
DECLARE_string(name);

SnakeApp::SnakeApp()
    : engine_{FLAGS_size, FLAGS_size},
      leaderboard_{cinder::app::getAssetPath(kDbPath).string()},
      paused_{false},
      player_name_{FLAGS_name},
      printed_game_over_{false},
      size_{FLAGS_size},
      speed_{FLAGS_speed},
      state_{GameState::kPlaying},
      tile_size_{FLAGS_tilesize},
      time_left_{0},
      food_color{kDefaultFoodColor} {}

void SnakeApp::setup() {
  cinder::gl::enableDepthWrite();
  cinder::gl::enableDepthRead();
  cinder::audio::SourceFileRef bgFile = load(loadAsset("Puzzle-Dreams-3.mp3"));
  background_music = cinder::audio::Voice::create(bgFile);
  background_music->start();
  start.time_since_epoch().zero();
  cinder::audio::SourceFileRef foodFile = load(loadAsset("smrpg_coin.wav"));
  food_music = cinder::audio::Voice::create(foodFile);
  engine_.SetLives(FLAGS_lives);
}

void SnakeApp::update() {
  if (state_ == GameState::kGameOver) {
    background_music->stop();
    snake::Player currentPlayer = {player_name_, engine_.GetScore()};
    if (top_players_.empty()) {
      leaderboard_.AddScoreToLeaderBoard(currentPlayer);
      top_players_ = leaderboard_.RetrieveHighScores(kLimit);
      // It is crucial the this vector be populated, given that `kLimit` > 0.
      assert(!top_players_.empty());
    }
    if (personal_bests_.empty()) {
      try {
        personal_bests_ =
            leaderboard_.RetrieveHighScores(currentPlayer, kLimit);
      } catch (const std::exception& e) {
        std::cout << e.what();
      }
    }
    return;
  } else if (!(background_music->isPlaying())) {
    background_music->start();
  }

  if (paused_) return;
  const auto time = system_clock::now();

  if (engine_.GetSnake().IsChopped()) {
    if (state_ != GameState::kCountDown) {
      state_ = GameState::kCountDown;
      last_intact_time_ = time;
    }

    // We must be in countdown.
    const auto time_in_countdown = time - last_intact_time_;
    if (time_in_countdown >= kCountdownTime) {
      state_ = GameState::kGameOver;
    }

    using std::chrono::seconds;
    const auto time_left_s =
        duration_cast<seconds>(kCountdownTime - time_in_countdown);
    time_left_ = static_cast<size_t>(
        std::min(kCountdownTime.count() - 1, time_left_s.count()));
  }

  if (time - last_time_ > std::chrono::milliseconds(speed_)) {
    engine_.Step();
    last_time_ = time;
  }
}

void SnakeApp::draw() {
  cinder::gl::enableAlphaBlending();

  if (state_ == GameState::kGameOver) {
    if (!printed_game_over_) cinder::gl::clear(Color(1, 0, 0));
    DrawGameOver();
    return;
  }

  if (paused_) return;

  cinder::gl::clear();
  DrawBackground();
  DrawSnake();
  if (prev_food_loc_ != engine_.GetFood().GetLocation()) {
    food_music->start();
    prev_food_loc_ = engine_.GetFood().GetLocation();
    food_color = kDefaultFoodColor;
  }
  DrawFood();
  DrawLives();
  if (state_ == GameState::kCountDown) DrawCountDown();
}

template <typename C>
void PrintText(const string& text, const C& color, const cinder::ivec2& size,
               const cinder::vec2& loc) {
  cinder::gl::color(color);

  auto box = TextBox()
                 .alignment(TextBox::CENTER)
                 .font(cinder::Font(kNormalFont, 30))
                 .size(size)
                 .color(color)
                 .backgroundColor(ColorA(0, 0, 0, 0))
                 .text(text);

  const auto box_size = box.getSize();
  const cinder::vec2 locp = {loc.x - box_size.x / 2, loc.y - box_size.y / 2};
  const auto surface = box.render();
  const auto texture = cinder::gl::Texture::create(surface);
  cinder::gl::draw(texture, locp);
}

float SnakeApp::PercentageOver() const {
  if (state_ != GameState::kCountDown) return 0.;

  using std::chrono::milliseconds;
  const double elapsed_time =
      duration_cast<milliseconds>(system_clock::now() - last_intact_time_)
          .count();
  const double countdown_time = milliseconds(kCountdownTime).count();
  const double percentage = elapsed_time / countdown_time;
  return static_cast<float>(percentage);
}

void SnakeApp::DrawBackground() const {
  const float percentage = PercentageOver();
  cinder::gl::clear(Color(percentage, 0, 0));
}

void SnakeApp::DrawLives() const {
  const Color color = Color::white();
  const cinder::ivec2 size = {500, 50};
  cinder::vec2 pos = {getWindowCenter().x, size.y};
  std::stringstream ss;
  ss << "Lives: " << engine_.GetLives();
  PrintText(ss.str(), color, size, pos);
}

void SnakeApp::DrawGameOver() {
  // Lazily print.
  if (printed_game_over_) return;
  if (top_players_.empty()) return;
  //  if (personal_bests_.empty()) return;
  const cinder::vec2 center = getWindowCenter();
  const cinder::ivec2 size = {500, 50};
  const Color color = Color::black();

  size_t row = 0;
  PrintText("Game Over :(", color, size, center);
  for (const snake::Player& player : top_players_) {
    std::stringstream ss;
    ss << player.name << " - " << player.score;
    PrintText(ss.str(), color, size, {center.x, center.y + (++row) * 50});
  }

  size_t personal_best_row = 0;
  PrintText("Personal Bests:", color, size, {center.x, 50});
  for (const snake::Player p : personal_bests_) {
    std::stringstream ss;
    ss << "Score: " << p.score;
    PrintText(ss.str(), color, size,
              {center.x, 50 + (++personal_best_row) * 50});
  }

  std::stringstream ss;
  ss << "Your Score: " << engine_.GetScore();
  PrintText(ss.str(), color, size, {center.x, center.y - 2 * size.y});

  printed_game_over_ = true;
}

void SnakeApp::DrawSnake() const {
  int num_visible = 0;
  for (const Segment& part : engine_.GetSnake()) {
    const Location loc = part.GetLocation();
    if (part.IsVisibile()) {
      const double opacity = std::exp(-(num_visible++) / kRate);
      cinder::gl::color(ColorA(0, 0, 1, static_cast<float>(opacity)));
    } else {
      const float percentage = PercentageOver();
      cinder::gl::color(Color(percentage, 0, 0));
    }
    cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                                    tile_size_ * loc.Col(),
                                    tile_size_ * loc.Row() + tile_size_,
                                    tile_size_ * loc.Col() + tile_size_));
  }
  const cinder::vec2 center = getWindowCenter();
}

void SnakeApp::DrawFood() {
  size_t ms_passed = 1000 * ci::app::getElapsedSeconds();
  size_t interval = (int)(1000 * (1.0/engine_.GetSnake().Size()));

  if ((ms_passed % interval) < (speed_/3)) {
    UpdateFoodColor();
  }

  cinder::gl::color(food_color.r, food_color.g, food_color.b);
  const Location loc = engine_.GetFood().GetLocation();
  cinder::gl::drawSolidRect(Rectf(tile_size_ * loc.Row(),
                                  tile_size_ * loc.Col(),
                                  tile_size_ * loc.Row() + tile_size_,
                                  tile_size_ * loc.Col() + tile_size_));
}

void SnakeApp::UpdateFoodColor() {
  // shifts the values of all colors
  float temp_blue = food_color.b;
  food_color.b = food_color.r;
  food_color.r = food_color.g;
  food_color.g = temp_blue;

}

void SnakeApp::DrawCountDown() const {
  const float percentage = PercentageOver();
  const string text = std::to_string(time_left_);
  const Color color = {1 - percentage, 0, 0};
  const cinder::ivec2 size = {50, 50};
  const cinder::vec2 loc = {50, 50};

  PrintText(text, color, size, loc);
}

void SnakeApp::keyDown(KeyEvent event) {
  switch (event.getCode()) {
    case KeyEvent::KEY_UP:
    case KeyEvent::KEY_k:
    case KeyEvent::KEY_w: {
      engine_.SetDirection(Direction::kLeft);
      break;
    }
    case KeyEvent::KEY_DOWN:
    case KeyEvent::KEY_j:
    case KeyEvent::KEY_s: {
      engine_.SetDirection(Direction::kRight);
      break;
    }
    case KeyEvent::KEY_LEFT:
    case KeyEvent::KEY_h:
    case KeyEvent::KEY_a: {
      engine_.SetDirection(Direction::kUp);
      break;
    }
    case KeyEvent::KEY_RIGHT:
    case KeyEvent::KEY_l:
    case KeyEvent::KEY_d: {
      engine_.SetDirection(Direction::kDown);
      break;
    }
    case KeyEvent::KEY_p: {
      paused_ = !paused_;

      if (paused_) {
        last_pause_time_ = system_clock::now();
      } else {
        last_intact_time_ += system_clock::now() - last_pause_time_;
      }
      break;
    }
    case KeyEvent::KEY_r: {
      ResetGame();
      break;
    }
  }
}

void SnakeApp::ResetGame() {
  engine_.Reset();
  paused_ = false;
  printed_game_over_ = false;
  state_ = GameState::kPlaying;
  time_left_ = 0;
  top_players_.clear();
}

}  // namespace snakeapp
