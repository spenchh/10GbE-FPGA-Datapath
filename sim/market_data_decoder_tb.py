import cocotb
from cocotb.clock import Clock
from cocotb.triggers import RisingEdge, ReadoOnly
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
    # TODO: drive all four inputs to their starting values
    i_reset_n.value = 0
    clock = Clock(dut.i_clk, 10, unit="ns") # Clock timing
    clock.start(start_high=False)

    # TODO: wait for rising edge and let outputs settle
    # TODO: Check every output agianst its least expected value