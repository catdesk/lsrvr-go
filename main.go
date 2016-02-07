package main

import(
    "fmt"
    "log"
    "encoding/json"
    "strings"
    "io/ioutil"

    "github.com/gin-gonic/gin"
    "github.com/tarm/serial"
)

type ColorMessage struct {
    Red       int
    Blue      int
    Green     int
    FadeSpeed int
}

func main() {
    r := gin.Default()
    r.GET("/", func(c *gin.Context) {
        c.JSON(200, gin.H{
            "message": "pong",
        })
    })
    r.POST("/", func(c *gin.Context) {
        var message ColorMessage
        err := c.BindJSON(&message)
        if err != nil {
            log.Println(err)
        }
        if message.FadeSpeed < 1 {
            message.FadeSpeed = 1
        }
        message.FadeSpeed = checkLimits(message.FadeSpeed)
        message.Red = checkLimits(message.Red)
        message.Green = checkLimits(message.Green)
        message.Blue = checkLimits(message.Blue)

        fmt.Printf("red: %d; green: %d; blue: %d; fadeSpeed: %d", message.Red, message.Green, message.Blue, message.FadeSpeed)
    })
    r.Run() // listen and server on 0.0.0.0:8080
}

func checkLimits(value int) int {
    if value < 0 {
        return 0
    } else if value > 255 {
        return 255
    } else {
        return value
    }
}

func passToSerial(message ColorMessage) string {
        c := &serial.Config{Name: findArduino(), Baud: 9600}
        s, err := serial.OpenPort(c)
        if err != nil {
                log.Fatal(err)
        }

        messageBytes, err := json.Marshal(message)
        n, err := s.Write(messageBytes)
        if err != nil {
                log.Fatal(err)
        }

        buf := make([]byte, 128)
        n, err = s.Read(buf)
        if err != nil {
                log.Fatal(err)
        }
        log.Printf("%q", buf[:n])
        return string(buf[:n])
}

// findArduino looks for the file that represents the Arduino
// serial connection. Returns the fully qualified path to the
// device if we are able to find a likely candidate for an
// Arduino, otherwise an empty string if unable to find
// something that 'looks' like an Arduino device.
func findArduino() string {
	contents, _ := ioutil.ReadDir("/dev")

	// Look for what is mostly likely the Arduino device
	for _, f := range contents {
		if strings.Contains(f.Name(), "tty.usbserial") ||
			strings.Contains(f.Name(), "ttyUSB") ||
			strings.Contains(f.Name(), "ttyACM") {
			return "/dev/" + f.Name()
		}
	}

	// Have not been able to find a USB device that 'looks'
	// like an Arduino.
	return ""
}
