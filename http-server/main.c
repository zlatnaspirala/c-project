
#include "include/httpd.h"

int main(int c, char **v)
{
  serve_forever("901");
  return 0;
}
void route()
{
  ROUTE_START()
  ROUTE_GET("/")
  {
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("Hello! You are using %s", request_header("User-Agent"));
  }
  ROUTE_POST("/")
  {
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("Wow, seems that you POSTed %d bytes. \r\n", payload_size);
    printf("Fetch the data using `payload` variable.");
  }

  ROUTE_POST("/test")
  {
    printf("TEST d%",  payload);
    printf("HTTP/1.1 200 OK\r\n\r\n");
    printf("Wow, seems that you POSTed %d bytes. \r\n", payload);
    printf("Fetch the data using `payload` variable.");
  }

  ROUTE_END()
}