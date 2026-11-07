
void __fastcall FUN_00410ed0(int param_1)

{
  wchar_t *pwVar1;
  wchar_t *pwVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  int extraout_ECX;
  int extraout_ECX_00;
  int extraout_ECX_01;
  int extraout_ECX_02;
  int extraout_ECX_03;
  int extraout_ECX_04;
  int extraout_ECX_05;
  int extraout_ECX_06;
  int extraout_ECX_07;
  void *pvVar8;
  void *local_3c;
  int local_38;
  int local_34;
  undefined1 *local_30;
  int local_2c;
  int local_28;
  uint local_24;
  undefined4 *local_20;
  uint local_1c;
  wchar_t *local_18;
  void *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00533c2c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  iVar5 = param_1;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x79,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x7a,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_00;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x7b,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_01;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x7c,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_02;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x7d,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_03;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x7f,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_04;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x80,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  iVar5 = extraout_ECX_05;
  FUN_004054f0(&stack0xffffffac,(short *)&DAT_0054bb58);
  FUN_00412bd0(&stack0xffffffb0,0x5a,iVar5);
  YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x34c),0);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x354),2);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x35c),1);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x364),3);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x36c),4);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x374),5);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 0x37c),6);
  YJXUI::MComboBox::SetCurSel(*(MComboBox **)(param_1 + 900),7);
  local_3c = (void *)0x0;
  local_38 = 0;
  local_34 = 0;
  local_8 = 0;
  iVar5 = *(int *)ThreadLocalStoragePointer;
  if ((*(int *)(iVar5 + 4) < DAT_0056ef90) &&
     (FUN_00448660(&DAT_0056ef90), iVar5 = extraout_ECX_06, DAT_0056ef90 == -1)) {
    local_8._0_1_ = 1;
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00448621(&DAT_0056ef90);
    iVar5 = extraout_ECX_07;
  }
  FUN_00407320(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),iVar5,(int *)&local_3c);
  local_24 = local_38 - (int)local_3c >> 2;
  local_1c = 0;
  pvVar8 = local_3c;
  if (local_24 != 0) {
    if (local_24 == 0) {
                    /* WARNING: Subroutine does not return */
      std::_Xout_of_range("invalid vector<T> subscript");
    }
    do {
      local_14 = *(void **)((int)pvVar8 + local_1c * 4);
      if (local_14 != (void *)0x0) {
        puVar7 = (undefined4 *)((int)local_14 + 0x28);
        local_20 = puVar7;
        piVar4 = FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
        pwVar1 = (wchar_t *)(piVar4 + 4);
        local_8._0_1_ = 2;
        local_18 = pwVar1;
        if ((*(int *)((int)local_14 + 0x18) == 0x16) || (*(int *)((int)local_14 + 0x18) == 0x17)) {
          local_30 = &stack0xffffffb8;
          piVar4 = FUN_00405df0(piVar4);
          puVar7 = FUN_004154c0(&local_2c,(wchar_t *)(piVar4 + 4));
          local_8._0_1_ = 4;
          FUN_00405aa0(&local_18,puVar7);
          local_8 = CONCAT31(local_8._1_3_,2);
          LOCK();
          piVar4 = (int *)(local_2c + -4);
          iVar5 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          puVar7 = local_20;
          if (iVar5 == 1 || iVar5 + -1 < 0) {
            (**(code **)(**(int **)(local_2c + -0x10) + 4))();
            puVar7 = local_20;
          }
        }
        else {
          pvVar8 = local_14;
          FUN_004054f0(&stack0xffffffb8,(short *)&DAT_0054bb58);
          iVar5 = _wtoi(pwVar1);
          puVar6 = FUN_00412bd0(&local_28,iVar5,(int)pvVar8);
          local_8._0_1_ = 3;
          FUN_00405aa0(&local_18,puVar6);
          local_8 = CONCAT31(local_8._1_3_,2);
          LOCK();
          piVar4 = (int *)(local_28 + -4);
          iVar5 = *piVar4;
          *piVar4 = *piVar4 + -1;
          UNLOCK();
          if (iVar5 == 1 || iVar5 + -1 < 0) {
            (**(code **)(**(int **)(local_28 + -0x10) + 4))();
          }
        }
        pwVar1 = local_18;
        if (0 < *(int *)(local_18 + -6)) {
          FUN_00405aa0(puVar7,&local_18);
        }
        iVar5 = *(int *)((int)local_14 + 0xc);
        if (iVar5 == 1) {
          YJXUI::MComboBox::SelectData
                    (*(MComboBox **)(param_1 + 0x34c),*(long *)((int)local_14 + 0x18));
          YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x34c),(wchar_t *)*puVar7);
          local_30 = &stack0xffffffb8;
          FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
LAB_004113d9:
          YJXUI::MouseCtrl::SetItemText(*(MouseCtrl **)(param_1 + 0x398));
        }
        else {
          if (iVar5 == 2) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x354),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x354),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 3) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x35c),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x35c),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 4) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x364),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x364),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 5) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x36c),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x36c),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 7) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x374),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x374),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 8) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 0x37c),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 0x37c),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
          if (iVar5 == 6) {
            YJXUI::MComboBox::SelectData
                      (*(MComboBox **)(param_1 + 900),*(long *)((int)local_14 + 0x18));
            YJXUI::MControlFont::SetTitle(*(MControlFont **)(param_1 + 900),(wchar_t *)*puVar7);
            local_30 = &stack0xffffffb8;
            FUN_00405df0((int *)(*(int *)((int)local_14 + 0x28) + -0x10));
            goto LAB_004113d9;
          }
        }
        pvVar8 = local_14;
        iVar3 = *(int *)((int)local_14 + 0x28);
        LOCK();
        piVar4 = (int *)(iVar3 + -4);
        iVar5 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar5 + -1 < 1) {
          (**(code **)(**(int **)(iVar3 + -0x10) + 4))();
        }
        iVar3 = *(int *)((int)pvVar8 + 0x14);
        LOCK();
        piVar4 = (int *)(iVar3 + -4);
        iVar5 = *piVar4;
        *piVar4 = *piVar4 + -1;
        UNLOCK();
        if (iVar5 == 1 || iVar5 + -1 < 0) {
          (**(code **)(**(int **)(iVar3 + -0x10) + 4))();
        }
        FUN_004484a6(pvVar8);
        local_8 = local_8 & 0xffffff00;
        LOCK();
        pwVar2 = pwVar1 + -2;
        iVar5 = *(int *)pwVar2;
        *(int *)pwVar2 = *(int *)pwVar2 + -1;
        UNLOCK();
        pvVar8 = local_3c;
        if (iVar5 == 1 || iVar5 + -1 < 0) {
          (**(code **)(**(int **)(pwVar1 + -8) + 4))();
          pvVar8 = local_3c;
        }
      }
      local_1c = local_1c + 1;
    } while (local_1c < local_24);
  }
  if (pvVar8 != (void *)0x0) {
    FUN_00406040(pvVar8,local_34 - (int)pvVar8 >> 2);
  }
  ExceptionList = local_10;
  return;
}

