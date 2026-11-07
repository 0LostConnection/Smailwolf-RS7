
void __fastcall FUN_004298c0(int param_1)

{
  MDialog *pMVar1;
  void *pvVar2;
  int iVar3;
  HWND__ *pHVar4;
  int *piVar5;
  undefined *this;
  int extraout_ECX;
  code *pcVar6;
  UINT UVar7;
  int iVar8;
  WPARAM WVar9;
  int iVar10;
  LPARAM LVar11;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00536118;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  timeBeginPeriod(1);
  if (*(int *)(param_1 + 0x3d8) == 0) {
    if (*(char *)(param_1 + 0x410) == '\0') {
      ExceptionList = local_10;
      return;
    }
    if (*(int *)(param_1 + 0x434) < 0xc9) {
      FUN_0042c9a0((MDialog *)(param_1 + -0x2b4));
    }
    else {
      FUN_00422510((void *)(param_1 + -0x2b4),0);
    }
  }
  else {
    iVar3 = *(int *)(**(int **)(param_1 + 0x3d4) + 8);
    piVar5 = (int *)**(undefined4 **)(param_1 + 0x3d4);
    *(int *)piVar5[1] = *piVar5;
    *(int *)(*piVar5 + 4) = piVar5[1];
    *(int *)(param_1 + 0x3d8) = *(int *)(param_1 + 0x3d8) + -1;
    free(piVar5);
    if (iVar3 == 2) {
      FUN_00429fa0((MDialog *)(param_1 + -0x2b4));
      FUN_00429ed0((MDialog *)(param_1 + -0x2b4));
    }
    else if (iVar3 == 3) {
      FUN_0042a080((MDialog *)(param_1 + -0x2b4));
    }
    pcVar6 = Sleep_exref;
    if (*(char *)(param_1 + 0x410) == '\0') {
      ExceptionList = local_10;
      return;
    }
    if (iVar3 == 1) {
      FUN_00429ed0((MDialog *)(param_1 + -0x2b4));
    }
    else if (iVar3 == 4) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042a130((MDialog *)(param_1 + -0x2b4));
      }
      else {
        FUN_00421920((MDialog *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 5) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        pMVar1 = (MDialog *)(param_1 + -0x2b4);
        FUN_00426000((int)pMVar1);
        FUN_00412630(pMVar1);
        *(undefined4 *)(param_1 + 0x440) = 0;
        FUN_00410ed0((int)pMVar1);
        FUN_004177f0(pMVar1);
        FUN_00418950(pMVar1);
      }
      else {
        FUN_00423f60((MDialog *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 0x11) {
      FUN_00424010((MDialog *)(param_1 + -0x2b4));
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 7) {
      FUN_0042a1d0(param_1 + -0x2b4);
      FUN_00410eb0((void *)(param_1 + -0x2b4));
      FUN_00418950((MDialog *)(param_1 + -0x2b4));
      FUN_004177f0((void *)(param_1 + -0x2b4));
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 6) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042ac40();
        FUN_0042b470();
        iVar3 = param_1 + -0x2b4;
        FUN_0042ba10(iVar3);
        FUN_0042b6b0(iVar3);
        FUN_0042b8d0(iVar3);
      }
      else {
        pvVar2 = (void *)(param_1 + -0x2b4);
        FUN_00424f10((int)pvVar2);
        FUN_004240f0((int)pvVar2);
        Sleep(100);
        FUN_00422c20(pvVar2);
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
      LVar11 = 1;
      WVar9 = 0;
      UVar7 = 0x6b2;
      pHVar4 = YJXUI::MWindow::GetSafeHwnd((MWindow *)(param_1 + -0x2b4));
      PostMessageW(pHVar4,UVar7,WVar9,LVar11);
    }
    else if (iVar3 == 8) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042b610(param_1 + -0x2b4);
      }
      else {
        FUN_00424e30(param_1 + -0x2b4);
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 9) {
      FUN_004169a0(param_1 + -0x2b4);
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 10) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042b6b0(param_1 + -0x2b4);
      }
      else {
        FUN_00421bf0((void *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 0xb) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042b8d0(param_1 + -0x2b4);
      }
      else {
        FUN_00421a40((void *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 0xc) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042ba10(param_1 + -0x2b4);
      }
      else {
        FUN_00421bf0((void *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      Sleep(100);
    }
    else if (iVar3 == 0xd) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042ba10(param_1 + -0x2b4);
      }
      else {
        FUN_00421bf0((void *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
    }
    else if (iVar3 == 0xf) {
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042b470();
        iVar3 = param_1 + -0x2b4;
        FUN_0042ba10(iVar3);
        FUN_0042b6b0(iVar3);
        FUN_0042b8d0(iVar3);
        FUN_0041b7f0(iVar3);
        *(undefined4 *)(param_1 + 0x444) = 0;
        FUN_004055b0(&local_14);
        local_8 = 2;
        FUN_00406540(&local_14,0x54a358);
        piVar5 = FUN_00405df0((int *)(local_14 + -0x10));
        piVar5 = piVar5 + 4;
        local_8._0_1_ = 3;
        iVar10 = extraout_ECX;
        FUN_004054f0(&stack0xffffffcc,L"light_mode");
        local_8._0_1_ = 4;
        iVar8 = *(int *)(param_1 + 0x43c);
        this = FUN_00401170();
        local_8 = CONCAT31(local_8._1_3_,2);
        FUN_00401860(this,iVar8,iVar10,(int)piVar5);
        FUN_004169a0(iVar3);
        local_8 = 0xffffffff;
        FUN_00405430(&local_14);
        pcVar6 = Sleep_exref;
      }
      else {
        FUN_004222d0((void *)(param_1 + -0x2b4));
        Sleep(100);
        FUN_00422c20((void *)(param_1 + -0x2b4));
      }
      if (*(MDialog **)(param_1 + 0xa28) != (MDialog *)0x0) {
        YJXUI::MDialog::DoOK(*(MDialog **)(param_1 + 0xa28));
      }
      (*pcVar6)();
      LVar11 = 2;
      WVar9 = 0;
      UVar7 = 0x6b2;
      pHVar4 = YJXUI::MWindow::GetSafeHwnd((MWindow *)(param_1 + -0x2b4));
      PostMessageW(pHVar4,UVar7,WVar9,LVar11);
    }
    else if (iVar3 == 0x10) {
      pMVar1 = (MDialog *)(param_1 + -0x2b4);
      if (*(int *)(param_1 + 0x434) < 0xc9) {
        FUN_0042c720(pMVar1);
        FUN_00418220(pMVar1,0);
        FUN_0041d5d0((void *)(param_1 + 0x18),0);
        FUN_0041b7f0((int)pMVar1);
      }
      else {
        FUN_00422400(pMVar1);
        Sleep(100);
        FUN_00422c20(pMVar1);
        FUN_0041b7f0((int)pMVar1);
      }
    }
  }
  timeEndPeriod(1);
  ExceptionList = local_10;
  return;
}

