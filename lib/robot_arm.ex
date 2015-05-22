defmodule RobotArm do

  #
  # OWI robot arm protocol at http://notbrainsurgery.livejournal.com/38622.html
  #

  # 0 byte commands
  @stop_arm_movement  0x00
  @grip_close         0x01
  @grip_open          0x02
  @wrist_up           0x04
  @wrist_down         0x08
  @elbow_up           0x10
  @elbow_down         0x20
  @shoulder_up        0x40
  @shoulder_down      0x80

  # 1st byte commands
  @stop_base                      0x00
  @rotate_base_clockwise          0x01
  @rotate_base_counter_clockwise  0x02

  # 2nd byte commands
  @led_off  0x00
  @led_on   0x01

  def init() do
    Process.flag(:trap_exit, true)
    port = Port.open({:spawn, "priv_dir/arm_usb"}, [{:packet, 2}])
    port
  end

  def all_stop(port) do
    Port.command(port, [@stop_arm_movement, @stop_base, @led_off])
  end

  def move_elbow(port, :up) do
    Port.command(port, [@elbow_up, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def move_elbow(port, :down) do
    Port.command(port, [@elbow_down, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def move_shoulder(port, :up) do
    Port.command(port, [@shoulder_up, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def move_shoulder(port, :down) do
    Port.command(port, [@shoulder_down, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def move_wrist(port, :up) do
    Port.command(port, [@wrist_up, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def move_wrist(port, :down) do
    Port.command(port, [@wrist_down, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def open_grip(port) do
    Port.command(port, [@grip_open, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def close_grip(port) do
    Port.command(port, [@grip_close, @stop_base, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def rotate_base(port, :clockwise) do
    Port.command(port, [@stop_arm_movement, @rotate_base_clockwise, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def rotate_base(port, :counter_clockwise) do
    Port.command(port, [@stop_arm_movement, @rotate_base_counter_clockwise, @led_off])
    :timer.sleep(250)
    all_stop(port)
  end

  def set_light(port, :on) do
    Port.command(port, [@stop_arm_movement, @stop_base, @led_on])
  end

  def set_light(port, :off) do
    Port.command(port, [@stop_arm_movement, @stop_base, @led_off])
  end

end
