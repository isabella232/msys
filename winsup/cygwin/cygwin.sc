OUTPUT_FORMAT(pei-i386)
SECTIONS
{
  .text  __image_base__ + __section_alignment__  :
  {
     *(.init)
    *(.text)
    *(SORT(.text$*))
    *(.glue_7t)
    *(.glue_7)
     ___CTOR_LIST__ = .; __CTOR_LIST__ = .;
			LONG (-1); *(.ctors); *(.ctor); LONG (0);
     ___DTOR_LIST__ = .; __DTOR_LIST__ = .;
			LONG (-1); *(.dtors); *(.dtor);  LONG (0);
     *(.fini)
    /* ??? Why is .gcc_exc here?  */
     *(.gcc_exc)
     etext = .;
    *(.gcc_except_table)
  }
  .autoload_text ALIGN(__section_alignment__) :
  {
    *(.*_autoload_text);
  }
  /* The Cygwin DLL uses a section to avoid copying certain data
     on fork.  This used to be named ".data".  The linker used
     to include this between __data_start__ and __data_end__, but that
     breaks building the cygwin32 dll.  Instead, we name the section
     ".data_cygwin_nocopy" and explictly include it after __data_end__. */
  .data ALIGN(__section_alignment__) :
  {
    __data_start__ = .;
    *(.data)
    *(.data2)
    *(SORT(.data$*))
    __data_end__ = .;
    *(.data_cygwin_nocopy)
  }
  .rdata ALIGN(__section_alignment__) :
  {
    *(.rdata)
    *(SORT(.rdata$*))
    *(.eh_frame)
  }
  .pdata ALIGN(__section_alignment__) :
  {
    *(.pdata)
  }
  .bss ALIGN(__section_alignment__) :
  {
    __bss_start__ = .;
    *(.bss)
    *(COMMON)
    __bss_end__ = .;
  }
  .edata ALIGN(__section_alignment__) :
  {
    *(.edata)
  }
  /DISCARD/ :
  {
    *(.debug$S)
    *(.debug$T)
    *(.debug$F)
    *(.drectve)
  }
  .idata ALIGN(__section_alignment__) :
  {
    /* This cannot currently be handled with grouped sections.
	See pe.em:sort_sections.  */
    SORT(*)(.idata$2)
    SORT(*)(.idata$3)
    /* These zeroes mark the end of the import list.  */
    LONG (0); LONG (0); LONG (0); LONG (0); LONG (0);
    SORT(*)(.idata$4)
    SORT(*)(.idata$5)
    SORT(*)(.idata$6)
    SORT(*)(.idata$7)
  }
  .CRT ALIGN(__section_alignment__) :
  {
    *(SORT(.CRT$*))
  }
  .endjunk ALIGN(__section_alignment__) :
  {
    /* end is deprecated, don't use it */
     end = .;
     _end = .;
     __end__ = .;
  }
  .cygwin_dll_common ALIGN(__section_alignment__):
  {
    *(.cygwin_dll_common)
  }
  .rsrc BLOCK(__section_alignment__) :
  {
    *(.rsrc)
    *(SORT(.rsrc$*))
  }
  .reloc BLOCK(__section_alignment__) :
  {
    *(.reloc)
  }
  .stab ALIGN(__section_alignment__) (NOLOAD) :
  {
    *(.stab)
  }
  .stabstr ALIGN(__section_alignment__) (NOLOAD) :
  {
    *(.stabstr)
  }
  /* DWARF 1.1 and DWARF 2 */
  .debug_aranges  ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_aranges) }
  .debug_pubnames ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_pubnames) }
  /* DWARF 2 */
  .debug_info     ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_info) }
  .debug_abbrev   ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_abbrev) }
  .debug_line     ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_line) }
  .debug_frame    ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_frame) }
  .debug_str      ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_str) }
  .debug_loc      ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_loc) }
  .debug_macinfo  ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_macinfo) }
  .debug_macinfo  ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_macinfo) }
  .debug_ranges   ALIGN(__section_alignment__) (NOLOAD) : { *(.debug_ranges) }
  .cygheap BLOCK(64 * 1024) :
  {
    __cygheap_start = ABSOLUTE(.) ;
    __system_dlls__ = ABSOLUTE(.) + 64;
  } 
}
