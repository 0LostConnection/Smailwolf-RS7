void __fastcall FUN_0042c9a0(MDialog *param_1)

{
  MDialog MVar1;
  DWORD DVar2;
  short *psVar3;
  int *piVar4;
  undefined *puVar5;
  MControl *pMVar6;
  MDialog extraout_CL;
  int extraout_ECX;
  int extraout_ECX_00;
  ColorButtonEx *this;
  int extraout_ECX_01;
  char extraout_DL;
  uint uVar7;
  char cVar8;
  int iVar9;
  int iVar10;
  int local_5c;
  undefined1 local_58 [2];
  char cStack_56;
  char cStack_55;
  char local_50;
  MDialog local_4f;
  MDialog local_4e;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00536714;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  DVar2 = GetTickCount();
  if (199 < DVar2 - *(int *)(param_1 + 0xba8)) {
    DVar2 = GetTickCount();
    *(DWORD *)(param_1 + 0xba8) = DVar2;
    memset(local_58,0,0x41);
    if (*(int *)(*(int *)ThreadLocalStoragePointer + 4) < DAT_0056ef18) {
      FUN_00448660(&DAT_0056ef18);
      if (DAT_0056ef18 == -1) {
        local_8 = 0;
        FUN_0043b7c0();
        _atexit(thunk_FUN_0043b8c0);
        local_8 = 0xffffffff;
        FUN_00448621(&DAT_0056ef18);
      }
    }
    if (DAT_0056ef10 < 0xc9) {
      if (DAT_0056eef0 != 0) {
        psVar3 = (short *)FUN_0043c9b0(0x56eef0);
        if (psVar3 != (short *)0x0) {
          FUN_0043e460(psVar3,local_58,0x15,1000);
        }
      }
    }
    else {
      FUN_0043f380();
    }
    cVar8 = (char)_local_58;
    uVar7 = (uint)_local_58 >> 8;
    if (cVar8 != '\0') {
      FUN_0043f380();
      local_4f = extraout_CL;
      local_50 = extraout_DL;
    }
    if (((cVar8 == -0x56) && ((char)uVar7 == -6)) && ((cStack_56 != '8' || (cStack_55 != '8')))) {
      if ((local_4f == (MDialog)0xff) || (local_4e == (MDialog)0xff)) {
        local_5c = 10;
        FUN_0040c780(param_1 + 0x688,&local_5c);
      }
      else if ((local_50 == 'P') || (local_50 == '`')) {
        FUN_00410450((uint)(byte)local_4f);
      }
      else if (local_50 == -0x30) {
        uVar7 = (uint)(byte)local_4f;
        if (100 < uVar7) {
          uVar7 = 100;
        }
        YJXUI::BatteryCtrl::SetBatteryInfo
                  (*(BatteryCtrl **)(param_1 + 0x2f4),uVar7,(uint)(byte)local_4e);
      }
      else if (local_50 == '\x10') {
        if (param_1[0x7c8] != local_4f) {
          param_1[0x7c8] = local_4f;
          if (local_4f == (MDialog)0x0) {
            param_1[0x7c8] = (MDialog)0x1;
          }
          else {
            iVar10 = atoi("5");
            if (iVar10 + 1 < (int)(uint)(byte)param_1[0x7c8]) {
              iVar10 = atoi("5");
              param_1[0x7c8] = (MDialog)((char)iVar10 + '\x01');
            }
          }
          FUN_004055b0(&local_5c);
          local_8 = 1;
          FUN_00406540(&local_5c,0x54a358);
          piVar4 = FUN_00405df0((int *)(local_5c + -0x10));
          piVar4 = piVar4 + 4;
          local_8._0_1_ = 2;
          iVar9 = extraout_ECX;
          FUN_004054f0(&stack0xffffff8c,L"dpi_index");
          local_8._0_1_ = 3;
          iVar10 = *(int *)(param_1 + 0x6f0);
          puVar5 = FUN_00401170();
          local_8 = CONCAT31(local_8._1_3_,1);
          FUN_00401860(puVar5,iVar10,iVar9,(int)piVar4);
          iVar10 = 1;
          *(uint *)(param_1 + 0x704) = (byte)param_1[0x7c8] + 100;
          pMVar6 = YJXUI::MDialog::GetControl(param_1,(byte)param_1[0x7c8] + 100);
          YJXUI::DPIControl::SetCheckState((DPIControl *)pMVar6,iVar10);
          pMVar6 = YJXUI::MDialog::GetControl(param_1,*(uint *)(param_1 + 0x704));
          iVar10 = YJXUI::DPIControl::GetDPIValue((DPIControl *)pMVar6);
          YJXUI::DPISlider::SetProgress(*(DPISlider **)(param_1 + 1000),iVar10 / 100);
          FUN_00405430(&local_5c);
        }
        param_1[0x7c9] = local_4e;
        FUN_004055b0(&local_5c);
        local_8 = 4;
        FUN_00406540(&local_5c,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_5c + -0x10));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 5;
        iVar9 = extraout_ECX_00;
        FUN_004054f0(&stack0xffffff8c,L"report_rate");
        local_8._0_1_ = 6;
        iVar10 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8 = CONCAT31(local_8._1_3_,4);
        FUN_00401860(puVar5,iVar10,iVar9,(int)piVar4);
        MVar1 = param_1[0x7c9];
        if (MVar1 == (MDialog)0x1) {
          this = *(ColorButtonEx **)(param_1 + 0x404);
        }
        else if (MVar1 == (MDialog)0x2) {
          this = *(ColorButtonEx **)(param_1 + 0x408);
        }
        else if (MVar1 == (MDialog)0x3) {
          this = *(ColorButtonEx **)(param_1 + 0x40c);
        }
        else {
          this = *(ColorButtonEx **)(param_1 + 0x410);
        }
        YJXUI::ColorButtonEx::SetCheck(this,1);
        FUN_00405430(&local_5c);
      }
      else if (local_50 == '\x11') {
        uVar7 = (uint)(byte)local_4f;
        if (6 < uVar7) {
          uVar7 = 6;
        }
        YJXUI::MComboBox::SelectData(*(MComboBox **)(param_1 + 0x428),uVar7);
        FUN_004055b0(&local_5c);
        local_8 = 7;
        FUN_00406540(&local_5c,0x54a358);
        piVar4 = FUN_00405df0((int *)(local_5c + -0x10));
        piVar4 = piVar4 + 4;
        local_8._0_1_ = 8;
        iVar9 = extraout_ECX_01;
        FUN_004054f0(&stack0xffffff8c,L"light_mode");
        local_8._0_1_ = 9;
        iVar10 = *(int *)(param_1 + 0x6f0);
        puVar5 = FUN_00401170();
        local_8 = CONCAT31(local_8._1_3_,7);
        FUN_00401860(puVar5,iVar10,iVar9,(int)piVar4);
        FUN_00405430(&local_5c);
      }
    }
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}


