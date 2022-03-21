# icosfitd Notes

This is a many-Selectee driver:
  - CMD command input
  - TM telemetry output
  - PTE output to icosfit (pseudo PTE.txt file)
  - SUM input from icosfit (pseudo ICOSsum.dat)

CMD: This interface servers as a standard command server
interface, but can also read commands directly from a file
for testing. In the latter case, we won't be setting any
file descriptor flags, but we will use gflag(1). For that,
we will set the fd to that of the input file.

TM: We won't try to set this up at all if we are reading
commands from a text file. Otherwise, it is a standard TM.

PTE: This is a simple output interface, and the protocol is such
that we never expect output to block, so this would not actually
require any flags at all. Unfortunately FIFOs are complicated,
so we need to add some timeouts before the file is even opened.
That means this one has to go into the event loop as -1. Looking
at the Selector source, it looks like it should be OK to update
fd when the file is opened, and also update it later if necessary.
The important condition to maintain is that all fds in the event
loop should be unique, or specific Selectees cannot be identified
during deletion.

SUM: This is simple input from the ICOSsum pipe. There is a special
case due to the pipe semantics that requires falling back to polling
until icosfit has opened the other end for write. Unlike with PTE,
this is after the fd is opened for read, so that's OK anyway.

For recovery in the event that icosfit fails on an individual scan
(which is entirely possible), we need to close both SUM and PTE.
Normally, I set fd = -1 on close, but that's not entirely cool
with respect to the Selector semantics. I will try it, but if
I run into trouble, an alternative approach would be to reuse the
fd by reopening with openfd() instead of open().