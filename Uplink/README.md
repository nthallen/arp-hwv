# Uplink

This directory contains two programs to provide UPD command upload
to the instruments on the ER-2 aircraft. In the initial iteration,
we will assume the GSE is directly connected to the aircraft network,
possibly via wireless. That probably means the GSE client will need
to be compiled under Monarch.

## uplink

uplink is a driver that runs on the Ground Support Equipment (GSE)
computer. It reads single-byte commands from the local command server,
formats them according to the UDP protocol, and writes transmits them
to the instrument's IP.


## uplink_rcvr

uplink_rcvr is the driver that runs on the instrument computer on
the aircraft. It reads single-byte codes from the serial port and
forwards them as software status instructions to the command
server.

