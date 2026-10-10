import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, FallingEdge, ReadOnly
from tools.gen_packet import packet_int

"""
Goal: Prove reset clears decoder correctly
    1. Drive i_rst_n = 0 to assert reset
    2. Drive i_packet_valid = 0 and i_packet_in = 0
    3. Generate a clock
    4. Wait for a rising edge while reset is low
    5. Use ReadOnly() to wait for output updates
    6. Check both flags and all eight decoded fields equal 0


"""
@cocotb.test(timeout_time=1, timeout_unit="us") # Max sim time allowed for test
async def test(dut):

    # RESET CHECK
    # drive all four inputs to their starting values
    dut.i_clk.value = 0
    dut.i_rst_n.value = 0
    dut.i_packet_valid.value = 0
    dut.i_packet_in.value = 0

    clock = Clock(dut.i_clk, 10, unit="ns") # Clock timing
    clock.start(start_high=False)

    # wait for rising edge and let outputs settle
    await RisingEdge(dut.i_clk)
    await ReadOnly() # Allows NBA region to settle

    # Check every output agianst its least expected value
    assert int(dut.o_decoded_valid.value)   == 0, "decoded_valid did not clear"
    assert int(dut.o_decode_error.value)    == 0, "decode_error did not clear"
    assert int(dut.o_message_type.value)    == 0, "message_type invalid"
    assert int(dut.o_sequence_number.value) == 0, "sequence_number invalid"
    assert int(dut.o_symbol_id.value)       == 0, "symbol_id invalid"
    assert int(dut.o_bid_price.value)       == 0, "bid_price invalid"
    assert int(dut.o_ask_price.value)       == 0, "ask_price invalid"
    assert int(dut.o_bid_size.value)        == 0, "bid_size invalid"
    assert int(dut.o_ask_size.value)        == 0, "ask_size invalid"
    assert int(dut.o_timestamp.value)       == 0, "timestamp invalid"


    # PACKET CHECK
    await FallingEdge(dut.i_clk) # Wait for falling edge to drive inputs

    dut.i_rst_n.value        = 1
    dut.i_packet_in.value    = packet_int
    dut.i_packet_valid.value = 1

    await RisingEdge(dut.i_clk)
    await ReadOnly()
    
    # Check decoded outputs
    assert int(dut.o_decoded_valid.value)   == 1, "decoded_valid did not assert"
    assert int(dut.o_decode_error.value)    == 0, "unexpected decode error"
    assert int(dut.o_message_type.value)    == 1, "message_type invalid"
    assert int(dut.o_sequence_number.value) == 42, "sequence_number mismatch"
    assert int(dut.o_symbol_id.value)       == 7, "symbol_id invalid"
    assert int(dut.o_bid_price.value)       == 1743100, "bid_price invalid"
    assert int(dut.o_ask_price.value)       == 1743300, "ask_price invalid"
    assert int(dut.o_bid_size.value)        == 800, "bid_size invalid"
    assert int(dut.o_ask_size.value)        == 500, "ask_size invalid"
    assert int(dut.o_timestamp.value)       == 123456789, "timestamp invalid"

    # IDLE CYCLE CHECK (no new packets)
    await FallingEdge(dut.i_clk)
    dut.i_packet_valid.value = 0
    dut.i_packet_in.value    = 0

    await RisingEdge(dut.i_clk)
    await ReadOnly()
    
    assert int(dut.o_decoded_valid.value)   == 0, "decoded_valid did not clear"   # no new decoded packet
    assert int(dut.o_decode_error.value)    == 0, "unexpected decode error"       # no packet = no error
    assert int(dut.o_message_type.value)    == 1, "message_type invalid"
    assert int(dut.o_sequence_number.value) == 42, "sequence_number mismatch"
    assert int(dut.o_symbol_id.value)       == 7, "symbol_id invalid"
    assert int(dut.o_bid_price.value)       == 1743100, "bid_price invalid"
    assert int(dut.o_ask_price.value)       == 1743300, "ask_price invalid"
    assert int(dut.o_bid_size.value)        == 800, "bid_size invalid"
    assert int(dut.o_ask_size.value)        == 500, "ask_size invalid"
    assert int(dut.o_timestamp.value)       == 123456789, "timestamp invalid"