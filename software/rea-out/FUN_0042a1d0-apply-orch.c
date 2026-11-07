
void __fastcall FUN_0042a1d0(int param_1)

{
  wchar_t *pwVar1;
  undefined4 uVar2;
  undefined4 *puVar3;
  int *piVar4;
  undefined *puVar5;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  int extraout_ECX_08;
  int extraout_ECX_09;
  int extraout_ECX_10;
  int extraout_ECX_11;
  int extraout_ECX_12;
  int extraout_ECX_13;
  int extraout_ECX_14;
  int extraout_ECX_15;
  int iVar6;
  char *pcVar7;
  int iVar8;
  wchar_t *local_198;
  char local_194 [9];
  undefined2 local_18b;
  char local_114 [128];
  char local_94 [9];
  undefined2 local_8b;
  char local_89;
  char local_87;
  char local_86;
  char local_85;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = -1;
  puStack_c = &LAB_005362e1;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  memset(local_194 + 1,0,0x7f);
  local_194[8] = *(char *)(param_1 + 0x6f0) - 1;
  local_194[0] = '\0';
  local_194[1] = 'U';
  local_194[2] = '0';
  local_194[3] = -0x5b;
  pcVar7 = local_194;
  local_194[4] = '\v';
  local_194[5] = '.';
  local_194[6] = '\0';
  local_194[7] = '\0';
  local_18b = 0;
  puVar3 = FUN_00401200();
  FUN_0043be10(puVar3,pcVar7);
  if ((local_194[0] == -0x56) && (local_194[1] == '0')) {
    YJXUI::BatteryCtrl::SetBatteryInfo
              (*(BatteryCtrl **)(param_1 + 0x2f4),(uint)(byte)local_194[8],(uint)(byte)local_18b);
  }
  uVar2 = *(undefined4 *)(param_1 + 0x6f0);
  local_198 = (wchar_t *)0x0;
  do {
    pwVar1 = (wchar_t *)((int)local_198 + 1);
    *(wchar_t **)(param_1 + 0x6f0) = pwVar1;
    memset(local_114 + 1,0,0x7f);
    local_114[8] = (char)local_198;
    pcVar7 = local_114;
    local_114[0] = '\0';
    local_114[1] = 'U';
    local_114[2] = '\b';
    local_114[3] = -0x5b;
    local_114[4] = '\v';
    local_114[5] = ' ';
    local_114[6] = '\0';
    local_114[7] = '\0';
    local_114[9] = '\0';
    local_114[10] = '\0';
    puVar3 = FUN_00401200();
    FUN_0043be10(puVar3,pcVar7);
    if (local_114[0] == -0x56) {
      iVar6 = 0;
      do {
        FUN_00411ce0(iVar6,(uint)(byte)local_114[iVar6 * 4 + 8],(uint)(byte)local_114[iVar6 * 4 + 9]
                     ,(uint)(byte)local_114[iVar6 * 4 + 10],(uint)(byte)local_114[iVar6 * 4 + 0xb]);
        iVar6 = iVar6 + 1;
      } while (iVar6 < 9);
    }
    local_198 = pwVar1;
  } while (pwVar1 < (wchar_t *)0x6);
  *(undefined4 *)(param_1 + 0x6f0) = uVar2;
  memset(local_94 + 1,0,0x7f);
  local_94[8] = *(char *)(param_1 + 0x6f0) + -1;
  local_94[0] = '\0';
  local_94[1] = 'U';
  local_94[2] = '\x0e';
  local_94[3] = -0x5b;
  pcVar7 = local_94;
  local_94[4] = '\v';
  local_94[5] = '.';
  local_94[6] = '\0';
  local_94[7] = '\0';
  local_8b = 0;
  puVar3 = FUN_00401200();
  FUN_0043be10(puVar3,pcVar7);
  if ((local_94[0] == -0x56) && (local_94[1] == '\x0e')) {
    FUN_004055b0((int *)&local_198);
    local_8 = 0;
    if (((char)local_8b != '\0') || ((local_8b._1_1_ != '\0' || (local_89 != '\0')))) {
      if ((local_87 == -1) && ((local_86 == -1 && (local_85 == -1)))) {
        FUN_0042ba10(param_1);
      }
      else {
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 1;
        iVar8 = extraout_ECX;
        FUN_004054f0(&stack0xfffffe44,L"light_mode");
        local_8._0_1_ = 2;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 3;
        iVar8 = extraout_ECX_00;
        FUN_004054f0(&stack0xfffffe44,L"report_rate");
        local_8._0_1_ = 4;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 5;
        iVar8 = extraout_ECX_01;
        FUN_004054f0(&stack0xfffffe44,L"dpi_flag");
        local_8._0_1_ = 6;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 7;
        iVar8 = extraout_ECX_02;
        FUN_004054f0(&stack0xfffffe44,L"dpi_count");
        local_8._0_1_ = 8;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 9;
        iVar8 = extraout_ECX_03;
        FUN_004054f0(&stack0xfffffe44,L"dpi_index");
        local_8._0_1_ = 10;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0xb;
          iVar8 = extraout_ECX_04;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group0_value");
          local_8._0_1_ = 0xc;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0xd;
          iVar8 = extraout_ECX_05;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group1_value");
          local_8._0_1_ = 0xe;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0xf;
          iVar8 = extraout_ECX_06;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group2_value");
          local_8._0_1_ = 0x10;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0x11;
          iVar8 = extraout_ECX_07;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group3_value");
          local_8._0_1_ = 0x12;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0x13;
          iVar8 = extraout_ECX_08;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group4_value");
          local_8._0_1_ = 0x14;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        pwVar1 = local_198;
        iVar6 = _wtoi(local_198);
        if (iVar6 - 0x32U < 0x655f) {
          piVar4 = FUN_00405df0((int *)(pwVar1 + -8));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 0x15;
          iVar8 = extraout_ECX_09;
          FUN_004054f0(&stack0xfffffe44,L"dpi_group5_value");
          local_8._0_1_ = 0x16;
          iVar6 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8._0_1_ = 0;
          FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        }
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x17;
        iVar8 = extraout_ECX_10;
        FUN_004054f0(&stack0xfffffe44,L"scroll_flag");
        local_8._0_1_ = 0x18;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x19;
        iVar8 = extraout_ECX_11;
        FUN_004054f0(&stack0xfffffe44,L"liftoff_height");
        local_8._0_1_ = 0x1a;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x1b;
        iVar8 = extraout_ECX_12;
        FUN_004054f0(&stack0xfffffe44,L"sensor_flag");
        local_8._0_1_ = 0x1c;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x1d;
        iVar8 = extraout_ECX_13;
        FUN_004054f0(&stack0xfffffe44,L"button_respondtime");
        local_8._0_1_ = 0x1e;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x1f;
        iVar8 = extraout_ECX_14;
        FUN_004054f0(&stack0xfffffe44,L"sleep_light");
        local_8._0_1_ = 0x20;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8._0_1_ = 0;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
        FUN_00406540(&local_198,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_198 + -8));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 0x21;
        iVar8 = extraout_ECX_15;
        FUN_004054f0(&stack0xfffffe44,L"e-sports_flag");
        local_8._0_1_ = 0x22;
        iVar6 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8 = (uint)local_8._1_3_ << 8;
        FUN_00401860(puVar5,iVar6,iVar8,(int)piVar4);
      }
    }
    FUN_00405430((int *)&local_198);
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

