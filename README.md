
------------------------------------------
# c-project
------------------------------------------

## Objective:
### - Learning lower levels
### - Minimal media server with recording feature and RTC/webRTC support.

### Description of structure:

  - devices - /multiplatform-capture/openpnp-capture
  - http-server ( c ) - Tested on macos 10.12.6
  - learn-c-code Basic's about `C` language syntax & language paradigma
  - Networking
    - nodejs/node-media-server
    - nodejs/node-jsffmpeg
    - c/server-client-basic1
    - c/server-client-basic2
    - c/server-client-terminal-chat

## Procedure to run share video output
#### nodejs/node-jsffmpeg

```js
node websocket-relay.js supersecret 8081 8082
npx http-server
```

### Run ffmpeg stream -  Test devices list on your computer

#### Mac OS
```bash
  ffmpeg -f avfoundation -list_devices true -i ""

  ffmpeg -f avfoundation -framerate 30 -video_size 640x480 
     -i /dev/video0 -f mpegts -codec:v mpeg1video -s 640x480 
     -b:v 1000k -bf 0 -muxdelay 0.001 http://localhost:8081/supersecret
```

#### Linux
```bash
  ffmpeg -f v4l2 -list_devices true -i ""

  ffmpeg -f v4l2 -framerate 25 -video_size 640x480 -i /dev/video0 
    -f mpegts -codec:v mpeg1video -s 640x480 -b:v 1000k 
    -bf 0 -muxdelay 0.001 http://localhost:8081/supersecret
```

#### Windows ####

```bash
  ffmpeg -list_devices true -f dshow -i dummy

  ffmpeg -f dshow -i video="USB Camera"  -framerate 30 
    -video_size 640x480 -f mpegts -codec:v mpeg2video -s 640x480 
    -rtbufsize 100M -b:v 1000k -bf 0 http://localhost:8081/supersecret

  ffmpeg -f dshow -i video="@device_pnp_\\?\usb#vid_0c45&pid_6340&mi_00#6&313cdc8e&0&0000#{65e8773d-8f56-11d0-a3b9-00a0c9223196}\global" 
   -framerate 30 -video_size 640x480 -f mpegts -codec:v mpeg2video -s 640x480 -rtbufsize 100M -b:v 1000k -bf 0 http://localhost:8081/supersecret

  ffmpeg -f dshow -i video="NVIDIA GeForce GTX 650 Ti BOOST" 
   -framerate 30 -video_size 640x480 -f mpegts -codec:v mpeg2video -s 640x480 -rtbufsize 100M -b:v 1000k -bf 0 http://localhost:8081/supersecret
```


## About `networking/`
 Socket libs are not in compatibility.
 For absolute compatibility we can count only on standard library (Math staff).
 
 For windows we need `winsock.h`.
 I only left cygwin to try with `POSIX` support.

  Worked:
  `networking\c\port-scanner-1\windows\`

 NOT TESTED : node-media-server project

 ### Notes for learning: 

 ```bash
  &amp; is the character reference for "An ampersand".
  -> &

  &gt;
  -> >

  &lt;
  -> <

 ```
