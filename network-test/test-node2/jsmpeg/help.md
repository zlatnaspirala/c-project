

  Runniong on MAC OS :

```bash
  ffmpeg -f avfoundation -framerate 30 -video_size 640x480 -i "0" -f mpegts -codec:v mpeg1video -s 640x480 -b:v 1000k -bf 0 -muxdelay 0.001 http://localhost:8081/supersecret
```

