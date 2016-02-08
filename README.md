# ltctrl-go

This is a rewrite of the existing Ruby software [url=https://github.com/whatisgravity/lctrl](lctrl), it only
covers the server lsrvr. lctrl provides a CLI interface to easily
interact with the server.


Simple command line interface to control RGB light strip, best used in
conjuction with the gem serialport-server but any service that takes in
messages from POST requests and passes them along to the serial port
will work. Using this you can control a RGB light strip connected to
another computer that is exposing an API.

Included is arduino code to accept json structures that provide
brightness of each red, blue and green between 0-255 and the speed of
which to fade to that brightness.

## Installation 

#### Server

Right now this requires the use of two separate repositories:

There is an install script included with each repository to simplyify
installation but the basic instructions are below:

Compile and install the binary

    git clone https://github.com/whatisgravity/lctrl-go
    cd lsrvr-go
    go build lsrvr.go
    sudo cp lsrvr /usr/local/bin/

#### Client

Install the dependencies

    git clone https://github.com/whatisgravity/lctrl
    bundle

To install it is best to put the lctrl executable your bin folder:

    cp lctrl /usr/local/bin

Then you copy the config file to your home directory, update the config
to suite your needs

    cp config/config.sample.yml ~/.lctrl.yml

Then start the server

    lsrvr --name desk --host 10.0.0.25

Then you can use the ltctrl command to control the lights.

## Usage

For the command line interface:

    Usage:
    Please specify colors by name, json or rgb:
        lctrl [options]
    Options:
        --server [option]       # Specify the server from the configuration file
        --red    [option]       # Provide a number 0-255, 0 being off and 255 being the brightest
        --green  [option]       # Provide a number 0-255, 0 being off and 255 being the brightest
        --blue   [option]       # Provide a number 0-255, 0 being off and 255 being the brightest
        --color  [option]       # Select between, "red", "blue", "green" or "white"
        --json   [json]         # Supply json directly: {"red": 0, "blue": 255, "green", 0}
        --random                # Randomly select a color
        --off                   # Turns off the lights
    Example:
        lctrl --green 255 --blue 24
        lctrl -g 255 -b 24

For the server:

    ## Light Server
      Usage:
      Please specify the server defined in the configuration to start:
          lsrvr [options]
      Options:
          --name  [option]   # Provide a name, if none default name (wall) will be used
          --host  [option]   # Provide a interface, if none default interface (0.0.0.0) will be used
          --port  [option]   # Provide a port, if none default port (8783) will be used
          --debug [option]   # Debug mode, if none default value (false) will be used

      Example:
          lsrvr --port=8080


## Roadmap

Port the lctrl client to golang.

It would be nice to be able to write favorite colors to the config file easy recall.

Change the arduino software and server software so instead of specifying
color, specify a pin and a value. Each pin can be :qualitative, which is
a range from 0-255 or quantitative, which is 0 or 1. Pins can should be able to be aliased to names
through a configuration file for ease of use:

    arduino:
      pin_count: 17
      pins:
        pin1:
          pin_type: :qualitative
          pin_name: "red"

This will allow for the system to be incredibly flexible and usable for a
variety of projects and not simply lights.
