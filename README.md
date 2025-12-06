PROTOCOL FRAME USING UART
--------------------------------------------------------------------------------
App transfer <CMD><DATA> where <CMD> contains 5 bits and <DATA> contains 15 bits
--------------------------------------------------------------------------------
Define              App send <CMD><DATA>              MCU TX 
Motor start         M_STR000000000000000              
Motor stop          M_STP000000000000000              
Motor inverse       M_INV000000000000000              
Motor speed         M_SPD000000000000070              
Motor PID           M_PID000000000654321                
Motor frequency     M_FRE000000000020000                
Motor response      M_PLT000000000000000              M_PLT<>
