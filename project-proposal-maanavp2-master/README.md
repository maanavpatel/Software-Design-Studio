# SimpleMovieMaker

Author: Maanav Patel

---

### What kind of project do you want to do? What background knowledge do you have on this kind of project, and why do you want to do this project?  

I want to create an application that can interface with my DSLR Camera to take photos and possibly create videos from existing photos. I have experience in photography and video editing and I know that there are times that I just want to go back and look at all my photos or send all my photos from one file (rather than using a slideshow or something). I don't have any experience with using other SDKs but from what I have seen so far it is well documented. If I was able to use this application to make said video it would solve my issue and therefore I am motivated to do this project. The reason I need to be able to do this with a camera rather than just pictures from a folder is so that I can easily make timelapse videos right as the pictures are taken. The main point for being able to interface with my Camera would be so that I can have a bigger display to use as a preview screen rather than having to spend money for an actual one.


### What specific external libraries will you need? Provide some links...

The main external library that I will help me to interface with my camera. I will have to use the Canon SDK Cinder block **[Cinder-CanonSdk](https://github.com/redpaperheart/Cinder-CanonSdk)** and possibly the libgphoto2 Cinder Block **[Cinder-GPhoto2](https://github.com/keithters/Cinder-GPhoto2)**. The libphoto2 block is noted as "In Progress" right now but since it is just a well known library that allows access to cameras and Canon has their own SDK, I may not need to use it. To create the video I am planning to use the already available MovieGl library as it looks like it has some features for creating videos frame by frame.


### Rough Timeline:

#### Week 1:

1. Get the new libraries set up
2. Connect Camera
3. Be able to take a picture through command line or function call

#### Week 2:

1. Create a display for the camera to use as a live view
2. Be able to see the live view from the camera on screen
3. Possibly add button(s)/ GUI elements to be able to take a picture or start timelapse sequence

#### Week 3:

1. Make sure all previous goals have been met
2. Create a video from images
3. Record some test footage

---

#### Extras:

If time permits and other functionality is working correctly, these are some possible extensions:

1. Add audio to videos
2. Use Open-CV/Face-tracker/etc. Cinder Block to only choose photos that include faces to make a video.
3. Add some filter or mask to the live preview or video.

