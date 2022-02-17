# SimpleCanonMovieMaker (In progress)
**Author**: Maanav Patel - [`maanavp2@illinois.edu`](mailto:maanavp2@illinois.edu)

[![license](https://img.shields.io/badge/license-MIT-green)](LICENSE)
[![docs](https://img.shields.io/badge/docs-yes-brightgreen)](docs/README.md)

Read [this document](https://cliutils.gitlab.io/modern-cmake/chapters/basics/structure.html) to understand the project
layout.

The [proposal](https://github.com/CS126SP20/final-project-maanavp2/blob/master/docs/PROPOSAL.md) for this project gives a better idea of what the ideal application would do.

### Features

Currently all modes are functioning properly. This application has multiple uses:
+ You can use this application to connect your Canon Camera and have a larger screen to preview your images instead of the viewfinder or small LCD.
+ Take pictures and instantly download them to your computer.
+ Create a video out of all the pictures taken during your session. 
+ Create a timelapse. Since some Canon's do not natively support 4k timelapse but take pictures in higher than 1080p resolution, this mode allows you to export a high quality timelapse and also store all the individual pictures so you can breakdown and see each frame without the need of a video editor.


## Dependencies

+ Canon SDK: apply for and download from: [Canon USA](http://consumer.usa.canon.com/cusa/support/consumer/eos_slr_camera_systems/eos_digital_slr_cameras/digital_rebel_xt?)
+ [Cinder](https://libcinder.org)
+ [Cinder-Canonsdk](https://github.com/redpaperheart/Cinder-CanonSdk)
+ [OpenCV2](https://opencv.org)
+ [cmake](https://cmake.org/)
+ gflags

## Usage

- Power on your Canon Camera. 
- Connect it to your computer using a USB cable.
- Wait for red LED to turn completely off. You may see a small computer symbol on your camera LCD.
- Run the program. (If failing to connect, check compatability with Canon SDK)

Follow gflags syntax

| Flag            |   Description/options                                       |
|-------------    |-------------------------------------------------------------|
| `--mode`        | `timelapse` , `stitch`, `camera`                            |                                               
| `--interval`    | The desired interval in seconds between pictures (min 3)    |
| `--num_of_pics` | The desired number of pictures to take total (min 1)        |
| `--fps`         | Framerate for live view |


* 'timelapse' takes pictures following given parameters and makes a video,
* 'stitch' allows u to create a video from your session,
* 'camera' allows you to take pictures only (Default)

## Controls

| Key       | Action                                                      |
|---------- |-------------------------------------------------------------|
| `f`       | Fullscreen.                                                 |
| `l`       | Toggle camera preview                                       |
| `SPACE`   | Take Photo                                                  |
| `ESC`     | Exit application (Triggers video creation in 'stitch' mode) |

