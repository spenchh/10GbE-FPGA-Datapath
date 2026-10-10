// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Symbol table implementation internals

#include "Vtop__pch.h"
#include "Vtop.h"
#include "Vtop___024root.h"

// FUNCTIONS
Vtop__Syms::~Vtop__Syms()
{

    // Tear down scope hierarchy
    __Vhier.remove(0, &__Vscope_market_data_decoder);

}

Vtop__Syms::Vtop__Syms(VerilatedContext* contextp, const char* namep, Vtop* modelp)
    : VerilatedSyms{contextp}
    // Setup internal state of the Syms class
    , __Vm_modelp{modelp}
    // Setup module instances
    , TOP{this, namep}
{
        // Check resources
        Verilated::stackCheck(25);
    // Configure time unit / time precision
    _vm_contextp__->timeunit(-9);
    _vm_contextp__->timeprecision(-9);
    // Setup each module's pointers to their submodules
    // Setup each module's pointer back to symbol table (for public functions)
    TOP.__Vconfigure(true);
    // Setup scopes
    __Vscope_TOP.configure(this, name(), "TOP", "TOP", "<null>", 0, VerilatedScope::SCOPE_OTHER);
    __Vscope_market_data_decoder.configure(this, name(), "market_data_decoder", "market_data_decoder", "market_data_decoder", -9, VerilatedScope::SCOPE_MODULE);

    // Set up scope hierarchy
    __Vhier.add(0, &__Vscope_market_data_decoder);

    // Setup export functions
    for (int __Vfinal = 0; __Vfinal < 2; ++__Vfinal) {
        __Vscope_TOP.varInsert(__Vfinal,"i_clk", &(TOP.i_clk), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_packet_in", &(TOP.i_packet_in), false, VLVT_WDATA,VLVD_IN|VLVF_PUB_RW,0,1 ,247,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_packet_valid", &(TOP.i_packet_valid), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"i_rst_n", &(TOP.i_rst_n), false, VLVT_UINT8,VLVD_IN|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_ask_price", &(TOP.o_ask_price), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_ask_size", &(TOP.o_ask_size), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_bid_price", &(TOP.o_bid_price), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_bid_size", &(TOP.o_bid_size), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_decode_error", &(TOP.o_decode_error), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_decoded_valid", &(TOP.o_decoded_valid), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_message_type", &(TOP.o_message_type), false, VLVT_UINT8,VLVD_OUT|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_sequence_number", &(TOP.o_sequence_number), false, VLVT_UINT32,VLVD_OUT|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_symbol_id", &(TOP.o_symbol_id), false, VLVT_UINT16,VLVD_OUT|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_TOP.varInsert(__Vfinal,"o_timestamp", &(TOP.o_timestamp), false, VLVT_UINT64,VLVD_OUT|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"i_clk", &(TOP.market_data_decoder__DOT__i_clk), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"i_packet_in", &(TOP.market_data_decoder__DOT__i_packet_in), false, VLVT_WDATA,VLVD_NODIR|VLVF_PUB_RW,0,1 ,247,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"i_packet_valid", &(TOP.market_data_decoder__DOT__i_packet_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"i_rst_n", &(TOP.market_data_decoder__DOT__i_rst_n), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_ask_price", &(TOP.market_data_decoder__DOT__incoming_ask_price), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_ask_size", &(TOP.market_data_decoder__DOT__incoming_ask_size), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_bid_price", &(TOP.market_data_decoder__DOT__incoming_bid_price), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_bid_size", &(TOP.market_data_decoder__DOT__incoming_bid_size), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_message_type", &(TOP.market_data_decoder__DOT__incoming_message_type), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_sequence_number", &(TOP.market_data_decoder__DOT__incoming_sequence_number), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_symbol_id", &(TOP.market_data_decoder__DOT__incoming_symbol_id), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"incoming_timestamp", &(TOP.market_data_decoder__DOT__incoming_timestamp), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_ask_price", &(TOP.market_data_decoder__DOT__o_ask_price), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_ask_size", &(TOP.market_data_decoder__DOT__o_ask_size), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_bid_price", &(TOP.market_data_decoder__DOT__o_bid_price), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_bid_size", &(TOP.market_data_decoder__DOT__o_bid_size), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_decode_error", &(TOP.market_data_decoder__DOT__o_decode_error), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_decoded_valid", &(TOP.market_data_decoder__DOT__o_decoded_valid), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_message_type", &(TOP.market_data_decoder__DOT__o_message_type), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,1 ,7,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_sequence_number", &(TOP.market_data_decoder__DOT__o_sequence_number), false, VLVT_UINT32,VLVD_NODIR|VLVF_PUB_RW,0,1 ,31,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_symbol_id", &(TOP.market_data_decoder__DOT__o_symbol_id), false, VLVT_UINT16,VLVD_NODIR|VLVF_PUB_RW,0,1 ,15,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"o_timestamp", &(TOP.market_data_decoder__DOT__o_timestamp), false, VLVT_UINT64,VLVD_NODIR|VLVF_PUB_RW,0,1 ,63,0);
        __Vscope_market_data_decoder.varInsert(__Vfinal,"packet_acceptable", &(TOP.market_data_decoder__DOT__packet_acceptable), false, VLVT_UINT8,VLVD_NODIR|VLVF_PUB_RW,0,0);
    }
}
