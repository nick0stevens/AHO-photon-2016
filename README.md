

Particle Setup
==============

**Associating the photon with your account**
There are several ways of uploading code to your photon board, but the easiest is by using the online IDE provided. However, before we do this we first need to associate the board with our account. Again there are several ways of doing this, but the easiest is to use the Particle moblie app.

download particle app for your phone from [iTunes](https://itunes.apple.com/us/app/particle-build-iot-projects/id991459054?mt=8), [google Play](https://play.google.com/store/apps/details?id=io.particle.android.app&hl=en) or [windows store](https://www.microsoft.com/en-us/store/p/particle/9nblggh4p55n)

**Dont use an existing password** as we may need to make this password visable and unencrypted online at some point.

Create a user profile and sign in. 

On the paged listed "Your devices" hit the + in the top right to add your new photon board. Select "Photon" from the options and follow the instructions. 

To ensure you select the correct photon, the 4 digit code that shows as part of the wifi network name is the same as the 2nd set of digits in the serial number found on the side of the photon packet.

Select the WPA2 network rather than the eduroam network. Enter the password details and hopefully you will be informed that you were successfull. If not its likely the password was incorrect. You have the opetion here to name the device or can accept the random name and replace it later.

Now that we have the photon associated with our account we want to check that we can control the board over the network. Select your new device and you will be shown an outline of the board. Tap D7 then digtialWrite. Tapping D7 again should switch the Pin on. It will read `HIGH` on the app and the onboard led on pin 7 on the associated photon will be lit. 

**Device Inspector**
Tapping the inspect button in the top right takes us to the Device Inspector. Here we can call functions and see variables. The current code uploaded to the Photon by default is called tinker and there are no variables to view. However, once you upload your own code you can see the results here. You can also copy the ID of your photon using the ticked icon on the info page. 

Tapping the 3 dots on the top right accesses a menu where you can re upload tinker or signal your device. This causes the central led to flash rainbows. This is useful if you are unsure which device is associated with your account. 

**Uploading code**
To upload code we need to use the online [particle IDE](https://www.particle.io/) on out laptop. Click on the IDE button on the topright and sign in. 
Here you can find sample code, add libraries, save your code etc.

We will run through an example in class but I suggest you have a look through this info on the [particle site] (https://docs.particle.io/guide/getting-started/build/photon/#web-ide)

**Adding Wifi networks**
You can store a number of networks and passwords on the board and it will automatically connect to any known networks it can find. In order to introduce it to the new network you need the RGB led blinking blue. If it is not already push the setup button for 3 seconds. Then use your mobile app and run through the steps to add it as if you ware adding a new photon. The board will still remenber the school network as well. 

**Differences with Arduino Uno**
While many aspects of the photon are similar including the code, there are a few difference that we need to be aware of.

* The Photon works on 3.3v rather than 5v as the arduino does. 
* Do not connect switches to the VIN pin as they may damage the switch pin.
* The Analog pins are 10 bit and so read from 0-4095 rather than 0-1023
* Remember not to publish data too often, otherwise you will get cut off from the particle server. So do not place `Particle.publish()` inside `void loop()`

**Useful Links**
[particle reference](https://docs.particle.io/reference/firmware/photon/#cloud-functions)

[indictation of the RGB meanings] (https://docs.particle.io/guide/getting-started/modes/photon/)

[description of pins](https://docs.particle.io/datasheets/photon-datasheet/#pin-description)

[online dashboard](http://jflasher.github.io/spark-helper/)

[detailed tutorials, course notes and examples from CMU](http://daraghbyrne.github.io/diotlabs/)

[linking your photon with P5.js](https://www.youtube.com/watch?v=0QjgnEBp__U&feature=youtu.be&list=PLRqwX-V7Uu6bYBG4PsCJpsvMka3boE9pR)

[interface with webpage with login](https://community.particle.io/t/web-page-sample-code-using-particle-api-js/21590)

<http://rickkas7.github.io/mustache/> Mustache template tester
