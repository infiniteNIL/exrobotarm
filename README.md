ExRobotArm
==========

Controls the OWI robot arm with Elixir (and a little C).

**Example:**

```elixir
port = RobotArm.init()
RobotArm.set_light(port, :on)
RobotArm.set_light(port, :off)

RobotArm.all_stop(port)

RobotArm.move_elbow(port, :up)
RobotArm.move_elbow(port, :down)
RobotArm.move_shoulder(port, :up)
RobotArm.move_shoulder(port, :down)
RobotArm.move_wrist(port, :up)
RobotArm.move_wrist(port, :down)

RobotArm.open_grip(port)
RobotArm.close_grip(port)

RobotArm.rotate_base(port, :clockwise)
RobotArm.rotate_base(port, :counter_clockwise)
```

**Dependencies**

Requires libusb to be installed. On Raspberry Pi you can do that with:

```
sudo apt-get install libusb-1.0
```

On Mac OS X do:

```
brew install libusb
```

You are using brew, aren't you? ;)
