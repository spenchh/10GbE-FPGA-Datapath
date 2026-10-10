// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design internal header
// See Vtop.h for the primary calling header

#ifndef VERILATED_VTOP___024ROOT_H_
#define VERILATED_VTOP___024ROOT_H_  // guard

#include "verilated.h"


class Vtop__Syms;

class alignas(VL_CACHE_LINE_BYTES) Vtop___024root final : public VerilatedModule {
  public:

    // DESIGN SPECIFIC STATE
    VL_IN8(i_clk,0,0);
    VL_IN8(i_rst_n,0,0);
    VL_IN8(i_packet_valid,0,0);
    VL_OUT8(o_decoded_valid,0,0);
    VL_OUT8(o_decode_error,0,0);
    VL_OUT8(o_message_type,7,0);
    CData/*0:0*/ market_data_decoder__DOT__i_clk;
    CData/*0:0*/ market_data_decoder__DOT__i_rst_n;
    CData/*0:0*/ market_data_decoder__DOT__i_packet_valid;
    CData/*0:0*/ market_data_decoder__DOT__o_decoded_valid;
    CData/*0:0*/ market_data_decoder__DOT__o_decode_error;
    CData/*7:0*/ market_data_decoder__DOT__o_message_type;
    CData/*7:0*/ market_data_decoder__DOT__incoming_message_type;
    CData/*0:0*/ market_data_decoder__DOT__packet_acceptable;
    CData/*0:0*/ __VstlFirstIteration;
    CData/*0:0*/ __VicoFirstIteration;
    CData/*0:0*/ __Vtrigprevexpr___TOP__i_clk__0;
    CData/*0:0*/ __VactContinue;
    VL_OUT16(o_symbol_id,15,0);
    SData/*15:0*/ market_data_decoder__DOT__o_symbol_id;
    SData/*15:0*/ market_data_decoder__DOT__incoming_symbol_id;
    VL_INW(i_packet_in,247,0,8);
    VL_OUT(o_sequence_number,31,0);
    VL_OUT(o_bid_price,31,0);
    VL_OUT(o_ask_price,31,0);
    VL_OUT(o_bid_size,31,0);
    VL_OUT(o_ask_size,31,0);
    VlWide<8>/*247:0*/ market_data_decoder__DOT__i_packet_in;
    IData/*31:0*/ market_data_decoder__DOT__o_sequence_number;
    IData/*31:0*/ market_data_decoder__DOT__o_bid_price;
    IData/*31:0*/ market_data_decoder__DOT__o_ask_price;
    IData/*31:0*/ market_data_decoder__DOT__o_bid_size;
    IData/*31:0*/ market_data_decoder__DOT__o_ask_size;
    IData/*31:0*/ market_data_decoder__DOT__incoming_sequence_number;
    IData/*31:0*/ market_data_decoder__DOT__incoming_bid_price;
    IData/*31:0*/ market_data_decoder__DOT__incoming_ask_price;
    IData/*31:0*/ market_data_decoder__DOT__incoming_bid_size;
    IData/*31:0*/ market_data_decoder__DOT__incoming_ask_size;
    IData/*31:0*/ __VactIterCount;
    VL_OUT64(o_timestamp,63,0);
    QData/*63:0*/ market_data_decoder__DOT__o_timestamp;
    QData/*63:0*/ market_data_decoder__DOT__incoming_timestamp;
    VlTriggerVec<1> __VstlTriggered;
    VlTriggerVec<1> __VicoTriggered;
    VlTriggerVec<1> __VactTriggered;
    VlTriggerVec<1> __VnbaTriggered;

    // INTERNAL VARIABLES
    Vtop__Syms* const vlSymsp;

    // CONSTRUCTORS
    Vtop___024root(Vtop__Syms* symsp, const char* v__name);
    ~Vtop___024root();
    VL_UNCOPYABLE(Vtop___024root);

    // INTERNAL METHODS
    void __Vconfigure(bool first);
};


#endif  // guard
