&command
  : AI Fix Row %d(Enter Row Number) * {
      if ( $4 < 0 || $4 > 0x3F )
	nl_error(2, "Requested row out of range" );
      else sbwr( 0xC01, 0x40 | $4 );
    }
  : AI Stop Engine * { sbwr( 0xC01, 0x80 ); }
  : AI Cycle Engine * { sbwr( 0xC01, 0 ); }
  : AI Reset * { sbwr( 0xC01, 0x400 ); }
  : AI Extra Settling * { sbwr( 0xC01, 0x200 ); }
  : AI Increment Row by %d(Enter Row Increment) * {
      if ( $5 < 0 || $5 > 0x3F )
	nl_error(2, "Requested row out of range" );
      else sbwr( 0xC01, 0x100 | $5 );
    }
  : AI Double Convert Always * { sbwr( 0xC01, 0x1800 ); }
  : AI Double Convert Row Zero * { sbwr( 0xC01, 0x0800 ); }
  ;
