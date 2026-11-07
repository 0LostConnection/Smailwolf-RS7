
void __fastcall FUN_0042ba10(int param_1)

{
  wchar_t *pwVar1;
  wchar_t *pwVar2;
  undefined4 uVar3;
  uint uVar4;
  int *piVar5;
  int iVar6;
  int iVar7;
  undefined *puVar8;
  undefined4 *this;
  undefined1 uVar9;
  int *extraout_ECX;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  int *extraout_ECX_02;
  int *extraout_ECX_03;
  int *extraout_ECX_04;
  uint uVar10;
  int extraout_ECX_05;
  int extraout_ECX_06;
  void *unaff_EDI;
  char *pcVar11;
  wchar_t **ppwVar12;
  wchar_t *local_a8;
  char local_a4 [9];
  char local_9b;
  undefined3 uStack_9a;
  undefined4 uStack_97;
  undefined4 uStack_93;
  undefined4 uStack_8f;
  undefined4 local_8b;
  undefined4 uStack_87;
  undefined4 uStack_83;
  undefined4 uStack_7f;
  undefined4 local_7b;
  undefined4 uStack_77;
  undefined4 uStack_73;
  undefined4 uStack_6f;
  undefined2 local_6b;
  undefined1 local_5c;
  undefined1 uStack_5b;
  undefined1 uStack_5a;
  undefined1 uStack_59;
  undefined4 uStack_58;
  undefined4 uStack_54;
  undefined4 uStack_50;
  undefined4 local_4c;
  undefined4 uStack_48;
  undefined4 uStack_44;
  undefined4 uStack_40;
  undefined4 local_3c;
  undefined4 uStack_38;
  undefined4 uStack_34;
  undefined4 uStack_30;
  undefined2 local_2c;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00536601;
  local_10 = ExceptionList;
  uVar4 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar4;
  memset(&local_5c,0,0x41);
  piVar5 = (int *)FUN_00406b10();
  if (piVar5 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  iVar6 = (**(code **)(*piVar5 + 0xc))();
  local_a8 = (wchar_t *)(iVar6 + 0x10);
  local_8 = 0;
  FUN_004054f0(&stack0xffffff3c,L"light_mode");
  local_8._0_1_ = 1;
  iVar6 = *(int *)ThreadLocalStoragePointer;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 2;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 1;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),uVar4,unaff_EDI);
  iVar7 = _wtoi(local_a8);
  _local_5c = CONCAT11((char)iVar7,local_5c);
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX;
  FUN_004054f0(&stack0xffffff44,L"report_rate");
  local_8._0_1_ = 3;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 4;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 3;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  _local_5c = CONCAT12((char)iVar7,_local_5c);
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX_00;
  FUN_004054f0(&stack0xffffff44,L"dpi_flag");
  local_8._0_1_ = 5;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 6;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 5;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  _wtoi(local_a8);
  _local_5c = CONCAT13(6,_local_5c);
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX_01;
  FUN_004054f0(&stack0xffffff44,L"dpi_index");
  local_8._0_1_ = 7;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 8;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 7;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uStack_58 = CONCAT31(uStack_58._1_3_,(char)iVar7 + '\x01');
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX_02;
  FUN_004054f0(&stack0xffffff44,L"dpi_group0_value");
  local_8._0_1_ = 9;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 10;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 9;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uVar3 = uStack_58;
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_58._3_1_ = SUB41(uVar3,3);
    uStack_58._0_3_ = CONCAT12((char)((uint)iVar7 >> 8),CONCAT11((char)iVar7,(undefined1)uStack_58))
    ;
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group1_value");
  local_8._0_1_ = 0xb;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0xc;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0xb;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_58 = CONCAT13((char)iVar7,(undefined3)uStack_58);
    uStack_54 = CONCAT31(uStack_54._1_3_,(char)((uint)iVar7 >> 8));
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group2_value");
  local_8._0_1_ = 0xd;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0xe;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0xd;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uVar3 = uStack_54;
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_54._3_1_ = SUB41(uVar3,3);
    uStack_54._0_3_ = CONCAT12((char)((uint)iVar7 >> 8),CONCAT11((char)iVar7,(undefined1)uStack_54))
    ;
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group3_value");
  local_8._0_1_ = 0xf;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x10;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0xf;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_54 = CONCAT13((char)iVar7,(undefined3)uStack_54);
    uStack_50 = CONCAT31(uStack_50._1_3_,(char)((uint)iVar7 >> 8));
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group4_value");
  local_8._0_1_ = 0x11;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x12;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x11;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uVar3 = uStack_50;
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_50._3_1_ = SUB41(uVar3,3);
    uStack_50._0_3_ = CONCAT12((char)((uint)iVar7 >> 8),CONCAT11((char)iVar7,(undefined1)uStack_50))
    ;
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group5_value");
  local_8._0_1_ = 0x13;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x14;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x13;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  piVar5 = (int *)(iVar7 - 0x32);
  if (piVar5 < (int *)0x655f) {
    uStack_50 = CONCAT13((char)iVar7,(undefined3)uStack_50);
    local_4c = CONCAT31(local_4c._1_3_,(char)((uint)iVar7 >> 8));
  }
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"dpi_group0_rgb");
  local_8._0_1_ = 0x15;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x16;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x15;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  local_4c = CONCAT13((char)(uVar4 >> 0x10),
                      CONCAT12((char)(uVar4 >> 8),CONCAT11((char)uVar4,(undefined1)local_4c)));
  FUN_004054f0(&stack0xffffff44,L"dpi_group1_rgb");
  local_8._0_1_ = 0x17;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x18;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x17;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  uStack_48 = CONCAT22(CONCAT11(uStack_48._3_1_,(char)(uVar4 >> 0x10)),(short)uVar4);
  FUN_004054f0(&stack0xffffff44,L"dpi_group2_rgb");
  local_8._0_1_ = 0x19;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x1a;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x19;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  uStack_48 = CONCAT13((char)uVar4,(undefined3)uStack_48);
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  uStack_44 = CONCAT31(CONCAT21(uStack_44._2_2_,(char)(uVar4 >> 0x10)),(char)(uVar4 >> 8));
  FUN_004054f0(&stack0xffffff44,L"dpi_group3_rgb");
  local_8._0_1_ = 0x1b;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x1c;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1b;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  uStack_40 = CONCAT31(uStack_40._1_3_,(char)(uVar4 >> 0x10));
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  uStack_44 = CONCAT13((char)(uVar4 >> 8),CONCAT12((char)uVar4,(undefined2)uStack_44));
  FUN_004054f0(&stack0xffffff44,L"dpi_group4_rgb");
  local_8._0_1_ = 0x1d;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x1e;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1d;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  uStack_40 = CONCAT13((char)(uVar4 >> 0x10),
                       CONCAT12((char)(uVar4 >> 8),CONCAT11((char)uVar4,(undefined1)uStack_40)));
  FUN_004054f0(&stack0xffffff44,L"dpi_group5_rgb");
  local_8._0_1_ = 0x1f;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x20;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1f;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  ppwVar12 = &local_a8;
  piVar5 = (int *)(uVar4 >> 8);
  local_3c = CONCAT22(CONCAT11(local_3c._3_1_,(char)(uVar4 >> 0x10)),(short)uVar4);
  FUN_004054f0(&stack0xffffff44,L"scroll_flag");
  local_8._0_1_ = 0x21;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x22;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x21;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uStack_34 = CONCAT31(uStack_34._1_3_,(char)iVar7);
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX_03;
  FUN_004054f0(&stack0xffffff44,L"liftoff_height");
  local_8._0_1_ = 0x23;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x24;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x23;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  iVar7 = _wtoi(local_a8);
  uStack_34._0_2_ = CONCAT11((char)iVar7,(undefined1)uStack_34);
  ppwVar12 = &local_a8;
  piVar5 = extraout_ECX_04;
  FUN_004054f0(&stack0xffffff44,L"sensor_flag");
  local_8._0_1_ = 0x25;
  if (*(int *)(iVar6 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 0x26;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x25;
      piVar5 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),(int)piVar5,ppwVar12);
  uVar4 = _wtoi(local_a8);
  uVar10 = 0;
  if ((uVar4 & 4) != 0) {
    uVar10 = 0x10;
  }
  uVar9 = (undefined1)uVar10;
  if ((uVar4 & 8) != 0) {
    uVar10 = uVar10 | 1;
    uVar9 = (undefined1)uVar10;
  }
  if ((uVar4 & 0x10) != 0) {
    uVar10 = uVar10 | 0x20;
    uVar9 = (undefined1)uVar10;
  }
  uStack_34 = CONCAT13(uStack_34._3_1_,CONCAT12(uVar9,(undefined2)uStack_34));
  ppwVar12 = &local_a8;
  FUN_004054f0(&stack0xffffff44,L"button_respondtime");
  local_8._0_1_ = 0x27;
  iVar6 = *(int *)(param_1 + 0x6f0);
  puVar8 = FUN_00401170();
  local_8._0_1_ = 0;
  FUN_00401a10(puVar8,iVar6,uVar10,ppwVar12);
  iVar6 = _wtoi(local_a8);
  uStack_34 = CONCAT13((char)iVar6,(undefined3)uStack_34);
  ppwVar12 = &local_a8;
  iVar7 = extraout_ECX_05;
  FUN_004054f0(&stack0xffffff44,L"sleep_light");
  local_8._0_1_ = 0x28;
  iVar6 = *(int *)(param_1 + 0x6f0);
  puVar8 = FUN_00401170();
  local_8._0_1_ = 0;
  FUN_00401a10(puVar8,iVar6,iVar7,ppwVar12);
  iVar6 = _wtoi(local_a8);
  uStack_30 = CONCAT31(uStack_30._1_3_,(char)iVar6);
  ppwVar12 = &local_a8;
  iVar7 = extraout_ECX_06;
  FUN_004054f0(&stack0xffffff44,L"e-sports_flag");
  local_8._0_1_ = 0x29;
  iVar6 = *(int *)(param_1 + 0x6f0);
  puVar8 = FUN_00401170();
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00401a10(puVar8,iVar6,iVar7,ppwVar12);
  pwVar2 = local_a8;
  iVar6 = _wtoi(local_a8);
  uStack_30._0_2_ = CONCAT11((char)iVar6,(undefined1)uStack_30);
  memset(local_a4 + 1,0,0x40);
  uStack_97 = uStack_58;
  uStack_93 = uStack_54;
  uStack_8f = uStack_50;
  local_6b = local_2c;
  local_a4[8] = *(char *)(param_1 + 0x6f0) + -1;
  pcVar11 = local_a4;
  local_a4[0] = '\0';
  local_a4[1] = 'U';
  local_a4[2] = '\x0f';
  local_a4[3] = -0x52;
  local_8b = local_4c;
  uStack_87 = uStack_48;
  uStack_83 = uStack_44;
  uStack_7f = uStack_40;
  local_a4[4] = '\n';
  local_a4[5] = '.';
  local_a4[6] = '\0';
  local_a4[7] = '\0';
  _local_9b = CONCAT31((int3)((uint)_local_5c >> 8),local_a4[8]);
  local_7b = local_3c;
  uStack_77 = uStack_38;
  uStack_73 = uStack_34;
  uStack_6f = uStack_30;
  this = FUN_00401200();
  FUN_0043be10(this,pcVar11);
  local_8 = 0xffffffff;
  LOCK();
  pwVar1 = pwVar2 + -2;
  iVar6 = *(int *)pwVar1;
  *(int *)pwVar1 = *(int *)pwVar1 + -1;
  UNLOCK();
  if (iVar6 == 1 || iVar6 + -1 < 0) {
    (**(code **)(**(int **)(pwVar2 + -8) + 4))();
  }
  ExceptionList = local_10;
  local_a8 = L"\xe58b썝쳌쳌譕櫬棿暊Sꅤ";
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

