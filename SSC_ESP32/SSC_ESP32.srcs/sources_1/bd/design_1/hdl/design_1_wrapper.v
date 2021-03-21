//Copyright 1986-2018 Xilinx, Inc. All Rights Reserved.
//--------------------------------------------------------------------------------
//Tool Version: Vivado v.2018.2 (win64) Build 2258646 Thu Jun 14 20:03:12 MDT 2018
//Date        : Sat Dec 12 14:29:17 2020
//Host        : DESKTOP-TRDTQOS running 64-bit major release  (build 9200)
//Command     : generate_target design_1_wrapper.bd
//Design      : design_1_wrapper
//Purpose     : IP block netlist
//--------------------------------------------------------------------------------
`timescale 1 ps / 1 ps

module design_1_wrapper
   (jxadc_pin10_io,
    jxadc_pin1_io,
    jxadc_pin2_io,
    jxadc_pin3_io,
    jxadc_pin4_io,
    jxadc_pin7_io,
    jxadc_pin8_io,
    jxadc_pin9_io,
    led_16bits_tri_o,
    push_buttons_4bits_tri_i,
    reset,
    sys_clock,
    usb_uart_rxd,
    usb_uart_txd);
  inout jxadc_pin10_io;
  inout jxadc_pin1_io;
  inout jxadc_pin2_io;
  inout jxadc_pin3_io;
  inout jxadc_pin4_io;
  inout jxadc_pin7_io;
  inout jxadc_pin8_io;
  inout jxadc_pin9_io;
  output [15:0]led_16bits_tri_o;
  input [3:0]push_buttons_4bits_tri_i;
  input reset;
  input sys_clock;
  input usb_uart_rxd;
  output usb_uart_txd;

  wire jxadc_pin10_i;
  wire jxadc_pin10_io;
  wire jxadc_pin10_o;
  wire jxadc_pin10_t;
  wire jxadc_pin1_i;
  wire jxadc_pin1_io;
  wire jxadc_pin1_o;
  wire jxadc_pin1_t;
  wire jxadc_pin2_i;
  wire jxadc_pin2_io;
  wire jxadc_pin2_o;
  wire jxadc_pin2_t;
  wire jxadc_pin3_i;
  wire jxadc_pin3_io;
  wire jxadc_pin3_o;
  wire jxadc_pin3_t;
  wire jxadc_pin4_i;
  wire jxadc_pin4_io;
  wire jxadc_pin4_o;
  wire jxadc_pin4_t;
  wire jxadc_pin7_i;
  wire jxadc_pin7_io;
  wire jxadc_pin7_o;
  wire jxadc_pin7_t;
  wire jxadc_pin8_i;
  wire jxadc_pin8_io;
  wire jxadc_pin8_o;
  wire jxadc_pin8_t;
  wire jxadc_pin9_i;
  wire jxadc_pin9_io;
  wire jxadc_pin9_o;
  wire jxadc_pin9_t;
  wire [15:0]led_16bits_tri_o;
  wire [3:0]push_buttons_4bits_tri_i;
  wire reset;
  wire sys_clock;
  wire usb_uart_rxd;
  wire usb_uart_txd;

  design_1 design_1_i
       (.jxadc_pin10_i(jxadc_pin10_i),
        .jxadc_pin10_o(jxadc_pin10_o),
        .jxadc_pin10_t(jxadc_pin10_t),
        .jxadc_pin1_i(jxadc_pin1_i),
        .jxadc_pin1_o(jxadc_pin1_o),
        .jxadc_pin1_t(jxadc_pin1_t),
        .jxadc_pin2_i(jxadc_pin2_i),
        .jxadc_pin2_o(jxadc_pin2_o),
        .jxadc_pin2_t(jxadc_pin2_t),
        .jxadc_pin3_i(jxadc_pin3_i),
        .jxadc_pin3_o(jxadc_pin3_o),
        .jxadc_pin3_t(jxadc_pin3_t),
        .jxadc_pin4_i(jxadc_pin4_i),
        .jxadc_pin4_o(jxadc_pin4_o),
        .jxadc_pin4_t(jxadc_pin4_t),
        .jxadc_pin7_i(jxadc_pin7_i),
        .jxadc_pin7_o(jxadc_pin7_o),
        .jxadc_pin7_t(jxadc_pin7_t),
        .jxadc_pin8_i(jxadc_pin8_i),
        .jxadc_pin8_o(jxadc_pin8_o),
        .jxadc_pin8_t(jxadc_pin8_t),
        .jxadc_pin9_i(jxadc_pin9_i),
        .jxadc_pin9_o(jxadc_pin9_o),
        .jxadc_pin9_t(jxadc_pin9_t),
        .led_16bits_tri_o(led_16bits_tri_o),
        .push_buttons_4bits_tri_i(push_buttons_4bits_tri_i),
        .reset(reset),
        .sys_clock(sys_clock),
        .usb_uart_rxd(usb_uart_rxd),
        .usb_uart_txd(usb_uart_txd));
  IOBUF jxadc_pin10_iobuf
       (.I(jxadc_pin10_o),
        .IO(jxadc_pin10_io),
        .O(jxadc_pin10_i),
        .T(jxadc_pin10_t));
  IOBUF jxadc_pin1_iobuf
       (.I(jxadc_pin1_o),
        .IO(jxadc_pin1_io),
        .O(jxadc_pin1_i),
        .T(jxadc_pin1_t));
  IOBUF jxadc_pin2_iobuf
       (.I(jxadc_pin2_o),
        .IO(jxadc_pin2_io),
        .O(jxadc_pin2_i),
        .T(jxadc_pin2_t));
  IOBUF jxadc_pin3_iobuf
       (.I(jxadc_pin3_o),
        .IO(jxadc_pin3_io),
        .O(jxadc_pin3_i),
        .T(jxadc_pin3_t));
  IOBUF jxadc_pin4_iobuf
       (.I(jxadc_pin4_o),
        .IO(jxadc_pin4_io),
        .O(jxadc_pin4_i),
        .T(jxadc_pin4_t));
  IOBUF jxadc_pin7_iobuf
       (.I(jxadc_pin7_o),
        .IO(jxadc_pin7_io),
        .O(jxadc_pin7_i),
        .T(jxadc_pin7_t));
  IOBUF jxadc_pin8_iobuf
       (.I(jxadc_pin8_o),
        .IO(jxadc_pin8_io),
        .O(jxadc_pin8_i),
        .T(jxadc_pin8_t));
  IOBUF jxadc_pin9_iobuf
       (.I(jxadc_pin9_o),
        .IO(jxadc_pin9_io),
        .O(jxadc_pin9_i),
        .T(jxadc_pin9_t));
endmodule
