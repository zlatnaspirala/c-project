
------------------------------------------
# c-project
------------------------------------------

## Objective: ##
### Minimal media server with recording feature and RTC/webRTC support. ###


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


### Test devices list on your computer. ###

#### Mac OS ####

```bash
  ffmpeg -f avfoundation -list_devices true -i ""
```

#### Linux ####

```bash
  ffmpeg -f v4l2 -list_devices true -i ""
```

#### Windows ####

 Socket libs are not in compatibility.
 For windows we need `winsock.h`.
 I only left cygwin to try with `POSIX` support.

  Worked:
  `networking\c\port-scanner-1\windows\`

 NOT TESTED : node-media-server project


 ### Notes for learning: ###

 ```bash
  &amp; is the character reference for "An ampersand".
  -> &

  &gt;
  -> >

  &lt;
  -> <

 ```
