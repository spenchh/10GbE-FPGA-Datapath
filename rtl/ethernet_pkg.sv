package ethernet_pkg;

parameter int BYTE      = 8;
parameter int DATAWIDTH = 64;
parameter int ENTRIES   = 256;

typedef enum logic {CAPTURE, INSPECT} packet_control_t;
typedef enum logic {LENGTH, TYPE} parse_control_t;    // controls wither LEN_TYPE is length or type
typedef enum logic {DST_ADDR, SRC_ADDR, LEN_TYPE, DATA, PAD, FCS, } state_control_t;

endpackage