# Simple_Droid_cam_client_Improved
Forked droidcam client from Fernando Fernández at Gitlab

I forked this from Fernando Fernández at Gitlab and made some improvements
This is still a work in progress and I dont know much about what I am doing :)
I will try to get in touch with the original creator and let him know of my fork

The improvements are that you can connect to a particular V4l2 device whereas before it was hard coded to /dev/video4....or was it 3?

This also lets you remove previoucs v4l2 devices and creates selected number of new v4l2 devices so you can run and connect to multiple ones

I made it so you can have multiple instances of Simple droidcam client

Things are a bit funky and it may take more than one try to connect to one device

The more than one instances can also be a bit funky, but it works. I have created and run more than one instance

As usual this software comes with no warranty of any kind and I am not responsible for any damages

Building and Installing:

  I am not sure about other distros so this is only for arch right now
  
   arch-meson . build --wrap-mode=nofallback
   
   ninja -C build

   ninja -C build install


 
P.S.   I am not sure what else you will need to build this. a good work around is to install the one from AUR which will pull in the dependencies,
        then build and install this one to replace that one.
