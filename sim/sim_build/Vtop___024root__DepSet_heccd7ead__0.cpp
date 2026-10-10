// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vtop.h for the primary calling header

#include "Vtop__pch.h"
#include "Vtop___024root.h"

void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VicoTriggered.word(0U))) {
        Vtop___024root___ico_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___ico_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___ico_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    vlSelfRef.market_data_decoder__DOT__i_clk = vlSelfRef.i_clk;
    vlSelfRef.market_data_decoder__DOT__i_rst_n = vlSelfRef.i_rst_n;
    vlSelfRef.market_data_decoder__DOT__i_packet_valid 
        = vlSelfRef.i_packet_valid;
    vlSelfRef.market_data_decoder__DOT__i_packet_in[0U] 
        = vlSelfRef.i_packet_in[0U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[1U] 
        = vlSelfRef.i_packet_in[1U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[2U] 
        = vlSelfRef.i_packet_in[2U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[3U] 
        = vlSelfRef.i_packet_in[3U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[4U] 
        = vlSelfRef.i_packet_in[4U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[5U] 
        = vlSelfRef.i_packet_in[5U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[6U] 
        = vlSelfRef.i_packet_in[6U];
    vlSelfRef.market_data_decoder__DOT__i_packet_in[7U] 
        = vlSelfRef.i_packet_in[7U];
    vlSelfRef.market_data_decoder__DOT__incoming_sequence_number 
        = ((vlSelfRef.i_packet_in[7U] << 0x10U) | (
                                                   vlSelfRef.i_packet_in[6U] 
                                                   >> 0x10U));
    vlSelfRef.market_data_decoder__DOT__incoming_symbol_id 
        = (0xffffU & vlSelfRef.i_packet_in[6U]);
    vlSelfRef.market_data_decoder__DOT__incoming_timestamp 
        = (((QData)((IData)(vlSelfRef.i_packet_in[1U])) 
            << 0x20U) | (QData)((IData)(vlSelfRef.i_packet_in[0U])));
    vlSelfRef.o_decoded_valid = vlSelfRef.market_data_decoder__DOT__o_decoded_valid;
    vlSelfRef.o_decode_error = vlSelfRef.market_data_decoder__DOT__o_decode_error;
    vlSelfRef.o_message_type = vlSelfRef.market_data_decoder__DOT__o_message_type;
    vlSelfRef.o_sequence_number = vlSelfRef.market_data_decoder__DOT__o_sequence_number;
    vlSelfRef.o_symbol_id = vlSelfRef.market_data_decoder__DOT__o_symbol_id;
    vlSelfRef.o_bid_price = vlSelfRef.market_data_decoder__DOT__o_bid_price;
    vlSelfRef.o_ask_price = vlSelfRef.market_data_decoder__DOT__o_ask_price;
    vlSelfRef.o_bid_size = vlSelfRef.market_data_decoder__DOT__o_bid_size;
    vlSelfRef.o_ask_size = vlSelfRef.market_data_decoder__DOT__o_ask_size;
    vlSelfRef.o_timestamp = vlSelfRef.market_data_decoder__DOT__o_timestamp;
    vlSelfRef.market_data_decoder__DOT__incoming_message_type 
        = (0xffU & (vlSelfRef.i_packet_in[7U] >> 0x10U));
    vlSelfRef.market_data_decoder__DOT__incoming_bid_price 
        = vlSelfRef.i_packet_in[5U];
    vlSelfRef.market_data_decoder__DOT__incoming_ask_price 
        = vlSelfRef.i_packet_in[4U];
    vlSelfRef.market_data_decoder__DOT__incoming_bid_size 
        = vlSelfRef.i_packet_in[3U];
    vlSelfRef.market_data_decoder__DOT__incoming_ask_size 
        = vlSelfRef.i_packet_in[2U];
    vlSelfRef.market_data_decoder__DOT__packet_acceptable 
        = ((1U == (IData)(vlSelfRef.market_data_decoder__DOT__incoming_message_type)) 
           & ((0U != vlSelfRef.market_data_decoder__DOT__incoming_bid_size) 
              & ((0U != vlSelfRef.market_data_decoder__DOT__incoming_ask_size) 
                 & (vlSelfRef.market_data_decoder__DOT__incoming_bid_price 
                    <= vlSelfRef.market_data_decoder__DOT__incoming_ask_price))));
}

void Vtop___024root___eval_triggers__ico(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__ico(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__ico\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VicoExecute;
    // Body
    Vtop___024root___eval_triggers__ico(vlSelf);
    __VicoExecute = vlSelfRef.__VicoTriggered.any();
    if (__VicoExecute) {
        Vtop___024root___eval_ico(vlSelf);
    }
    return (__VicoExecute);
}

void Vtop___024root___eval_act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
}

void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf);

void Vtop___024root___eval_nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if ((1ULL & vlSelfRef.__VnbaTriggered.word(0U))) {
        Vtop___024root___nba_sequent__TOP__0(vlSelf);
    }
}

VL_INLINE_OPT void Vtop___024root___nba_sequent__TOP__0(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___nba_sequent__TOP__0\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (vlSelfRef.i_rst_n) {
        vlSelfRef.market_data_decoder__DOT__o_decode_error = 0U;
        vlSelfRef.market_data_decoder__DOT__o_decoded_valid = 0U;
        if (vlSelfRef.i_packet_valid) {
            if ((1U & (~ (IData)(vlSelfRef.market_data_decoder__DOT__packet_acceptable)))) {
                vlSelfRef.market_data_decoder__DOT__o_decode_error = 1U;
            }
            if (vlSelfRef.market_data_decoder__DOT__packet_acceptable) {
                vlSelfRef.market_data_decoder__DOT__o_decoded_valid = 1U;
                vlSelfRef.market_data_decoder__DOT__o_sequence_number 
                    = vlSelfRef.market_data_decoder__DOT__incoming_sequence_number;
                vlSelfRef.market_data_decoder__DOT__o_symbol_id 
                    = vlSelfRef.market_data_decoder__DOT__incoming_symbol_id;
                vlSelfRef.market_data_decoder__DOT__o_timestamp 
                    = vlSelfRef.market_data_decoder__DOT__incoming_timestamp;
                vlSelfRef.market_data_decoder__DOT__o_ask_price 
                    = vlSelfRef.market_data_decoder__DOT__incoming_ask_price;
                vlSelfRef.market_data_decoder__DOT__o_ask_size 
                    = vlSelfRef.market_data_decoder__DOT__incoming_ask_size;
                vlSelfRef.market_data_decoder__DOT__o_message_type 
                    = vlSelfRef.market_data_decoder__DOT__incoming_message_type;
                vlSelfRef.market_data_decoder__DOT__o_bid_price 
                    = vlSelfRef.market_data_decoder__DOT__incoming_bid_price;
                vlSelfRef.market_data_decoder__DOT__o_bid_size 
                    = vlSelfRef.market_data_decoder__DOT__incoming_bid_size;
            }
        }
    } else {
        vlSelfRef.market_data_decoder__DOT__o_decode_error = 0U;
        vlSelfRef.market_data_decoder__DOT__o_decoded_valid = 0U;
        vlSelfRef.market_data_decoder__DOT__o_sequence_number = 0U;
        vlSelfRef.market_data_decoder__DOT__o_symbol_id = 0U;
        vlSelfRef.market_data_decoder__DOT__o_timestamp = 0ULL;
        vlSelfRef.market_data_decoder__DOT__o_ask_price = 0U;
        vlSelfRef.market_data_decoder__DOT__o_ask_size = 0U;
        vlSelfRef.market_data_decoder__DOT__o_message_type = 0U;
        vlSelfRef.market_data_decoder__DOT__o_bid_price = 0U;
        vlSelfRef.market_data_decoder__DOT__o_bid_size = 0U;
    }
    vlSelfRef.o_decode_error = vlSelfRef.market_data_decoder__DOT__o_decode_error;
    vlSelfRef.o_decoded_valid = vlSelfRef.market_data_decoder__DOT__o_decoded_valid;
    vlSelfRef.o_sequence_number = vlSelfRef.market_data_decoder__DOT__o_sequence_number;
    vlSelfRef.o_symbol_id = vlSelfRef.market_data_decoder__DOT__o_symbol_id;
    vlSelfRef.o_timestamp = vlSelfRef.market_data_decoder__DOT__o_timestamp;
    vlSelfRef.o_ask_price = vlSelfRef.market_data_decoder__DOT__o_ask_price;
    vlSelfRef.o_ask_size = vlSelfRef.market_data_decoder__DOT__o_ask_size;
    vlSelfRef.o_message_type = vlSelfRef.market_data_decoder__DOT__o_message_type;
    vlSelfRef.o_bid_price = vlSelfRef.market_data_decoder__DOT__o_bid_price;
    vlSelfRef.o_bid_size = vlSelfRef.market_data_decoder__DOT__o_bid_size;
}

void Vtop___024root___eval_triggers__act(Vtop___024root* vlSelf);

bool Vtop___024root___eval_phase__act(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__act\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    VlTriggerVec<1> __VpreTriggered;
    CData/*0:0*/ __VactExecute;
    // Body
    Vtop___024root___eval_triggers__act(vlSelf);
    __VactExecute = vlSelfRef.__VactTriggered.any();
    if (__VactExecute) {
        __VpreTriggered.andNot(vlSelfRef.__VactTriggered, vlSelfRef.__VnbaTriggered);
        vlSelfRef.__VnbaTriggered.thisOr(vlSelfRef.__VactTriggered);
        Vtop___024root___eval_act(vlSelf);
    }
    return (__VactExecute);
}

bool Vtop___024root___eval_phase__nba(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_phase__nba\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    CData/*0:0*/ __VnbaExecute;
    // Body
    __VnbaExecute = vlSelfRef.__VnbaTriggered.any();
    if (__VnbaExecute) {
        Vtop___024root___eval_nba(vlSelf);
        vlSelfRef.__VnbaTriggered.clear();
    }
    return (__VnbaExecute);
}

#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__ico(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__nba(Vtop___024root* vlSelf);
#endif  // VL_DEBUG
#ifdef VL_DEBUG
VL_ATTR_COLD void Vtop___024root___dump_triggers__act(Vtop___024root* vlSelf);
#endif  // VL_DEBUG

void Vtop___024root___eval(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Init
    IData/*31:0*/ __VicoIterCount;
    CData/*0:0*/ __VicoContinue;
    IData/*31:0*/ __VnbaIterCount;
    CData/*0:0*/ __VnbaContinue;
    // Body
    __VicoIterCount = 0U;
    vlSelfRef.__VicoFirstIteration = 1U;
    __VicoContinue = 1U;
    while (__VicoContinue) {
        if (VL_UNLIKELY(((0x64U < __VicoIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__ico(vlSelf);
#endif
            VL_FATAL_MT("/mnt/c/Users/HP/Documents/10GbE-FPGA-Datapath/rtl/market_data_decoder.sv", 6, "", "Input combinational region did not converge.");
        }
        __VicoIterCount = ((IData)(1U) + __VicoIterCount);
        __VicoContinue = 0U;
        if (Vtop___024root___eval_phase__ico(vlSelf)) {
            __VicoContinue = 1U;
        }
        vlSelfRef.__VicoFirstIteration = 0U;
    }
    __VnbaIterCount = 0U;
    __VnbaContinue = 1U;
    while (__VnbaContinue) {
        if (VL_UNLIKELY(((0x64U < __VnbaIterCount)))) {
#ifdef VL_DEBUG
            Vtop___024root___dump_triggers__nba(vlSelf);
#endif
            VL_FATAL_MT("/mnt/c/Users/HP/Documents/10GbE-FPGA-Datapath/rtl/market_data_decoder.sv", 6, "", "NBA region did not converge.");
        }
        __VnbaIterCount = ((IData)(1U) + __VnbaIterCount);
        __VnbaContinue = 0U;
        vlSelfRef.__VactIterCount = 0U;
        vlSelfRef.__VactContinue = 1U;
        while (vlSelfRef.__VactContinue) {
            if (VL_UNLIKELY(((0x64U < vlSelfRef.__VactIterCount)))) {
#ifdef VL_DEBUG
                Vtop___024root___dump_triggers__act(vlSelf);
#endif
                VL_FATAL_MT("/mnt/c/Users/HP/Documents/10GbE-FPGA-Datapath/rtl/market_data_decoder.sv", 6, "", "Active region did not converge.");
            }
            vlSelfRef.__VactIterCount = ((IData)(1U) 
                                         + vlSelfRef.__VactIterCount);
            vlSelfRef.__VactContinue = 0U;
            if (Vtop___024root___eval_phase__act(vlSelf)) {
                vlSelfRef.__VactContinue = 1U;
            }
        }
        if (Vtop___024root___eval_phase__nba(vlSelf)) {
            __VnbaContinue = 1U;
        }
    }
}

#ifdef VL_DEBUG
void Vtop___024root___eval_debug_assertions(Vtop___024root* vlSelf) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vtop___024root___eval_debug_assertions\n"); );
    Vtop__Syms* const __restrict vlSymsp VL_ATTR_UNUSED = vlSelf->vlSymsp;
    auto& vlSelfRef = std::ref(*vlSelf).get();
    // Body
    if (VL_UNLIKELY(((vlSelfRef.i_clk & 0xfeU)))) {
        Verilated::overWidthError("i_clk");}
    if (VL_UNLIKELY(((vlSelfRef.i_rst_n & 0xfeU)))) {
        Verilated::overWidthError("i_rst_n");}
    if (VL_UNLIKELY(((vlSelfRef.i_packet_valid & 0xfeU)))) {
        Verilated::overWidthError("i_packet_valid");}
    if (VL_UNLIKELY(((vlSelfRef.i_packet_in[7U] & 0xff000000U)))) {
        Verilated::overWidthError("i_packet_in");}
}
#endif  // VL_DEBUG
