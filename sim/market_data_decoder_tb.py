import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ReadOnly
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