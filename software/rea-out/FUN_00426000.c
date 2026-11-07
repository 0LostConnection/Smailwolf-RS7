
void __fastcall FUN_00426000(int param_1)

{
  wchar_t *pwVar1;
  void *pvVar2;
  void *pvVar3;
  int iVar4;
  wchar_t *pwVar5;
  int iVar6;
  undefined *puVar7;
  int *piVar8;
  undefined4 *puVar9;
  uint uVar10;
  int extraout_ECX;
  undefined4 *puVar11;
  uint uVar12;
  int iVar13;
  undefined4 uVar14;
  undefined4 local_50;
  int local_4c;
  int local_48 [3];
  void *local_3c;
  void *local_38;
  int local_34;
  undefined *local_30;
  undefined4 *local_2c;
  int local_28;
  int local_24;
  int local_20;
  int local_1c;
  uint local_18;
  wchar_t *local_14;
  void *local_10;
  undefined1 *puStack_c;
  uint local_8;
  
  puStack_c = &LAB_00535b1c;
  local_10 = ExceptionList;
  ExceptionList = &local_10;
  local_3c = (void *)0x0;
  local_38 = (void *)0x0;
  local_34 = 0;
  local_8 = 0;
  iVar13 = *(int *)ThreadLocalStoragePointer;
  local_24 = iVar13;
  local_20 = param_1;
  if ((*(int *)(iVar13 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
    local_8._0_1_ = 1;
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00448621(&DAT_0056ef90);
  }
  iVar6 = FUN_00403810(&DAT_0056ef20,(int *)&local_3c);
  if (iVar6 < 1) {
    FUN_004010b0(&local_50);
    local_8._0_1_ = 2;
    FUN_00406540(&local_4c,0x54a358);
    puVar9 = &local_50;
    puVar7 = FUN_00401170();
    FUN_00403690(puVar7,(int)puVar9);
    FUN_00406540(&local_4c,0x54a358);
    puVar9 = &local_50;
    puVar7 = FUN_00401170();
    FUN_00403690(puVar7,(int)puVar9);
    FUN_00406540(&local_4c,0x54a358);
    puVar9 = &local_50;
    puVar7 = FUN_00401170();
    FUN_00403690(puVar7,(int)puVar9);
    FUN_00406540(&local_4c,0x54a358);
    puVar9 = &local_50;
    puVar7 = FUN_00401170();
    FUN_00403690(puVar7,(int)puVar9);
    FUN_00406540(&local_4c,0x54a358);
    puVar9 = &local_50;
    puVar7 = FUN_00401170();
    FUN_00403690(puVar7,(int)puVar9);
    iVar6 = 1;
    puVar7 = FUN_00401170();
    FUN_004044b0(puVar7,iVar6);
    local_8 = (uint)local_8._1_3_ << 8;
    LOCK();
    piVar8 = (int *)(local_48[0] + -4);
    iVar6 = *piVar8;
    *piVar8 = *piVar8 + -1;
    UNLOCK();
    if (iVar6 + -1 < 1) {
      (**(code **)(**(int **)(local_48[0] + -0x10) + 4))();
    }
    LOCK();
    piVar8 = (int *)(local_4c + -4);
    iVar6 = *piVar8;
    *piVar8 = *piVar8 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(local_4c + -0x10) + 4))();
    }
  }
  YJXUI::MComboBox::DelAllItems(*(MComboBox **)(param_1 + 0x344));
  if ((*(int *)(iVar13 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
    local_8._0_1_ = 3;
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    local_8 = (uint)local_8._1_3_ << 8;
    FUN_00448621(&DAT_0056ef90);
  }
  local_1c = FUN_00403810(&DAT_0056ef20,(int *)&local_3c);
  pvVar3 = local_3c;
  uVar12 = 0;
  if (0 < local_1c) {
    uVar10 = (int)local_38 - (int)local_3c >> 2;
    local_18 = uVar10;
    do {
      if (uVar10 <= uVar12) goto LAB_00426591;
      local_2c = *(undefined4 **)((int)pvVar3 + uVar12 * 4);
      if (local_2c != (undefined4 *)0x0) {
        piVar8 = FUN_00405df0((int *)(local_2c[1] + -0x10));
        local_8._0_1_ = 4;
        iVar13 = extraout_ECX;
        local_14 = (wchar_t *)(piVar8 + 4);
        FUN_004054f0(&stack0xffffffa0,(short *)&DAT_0054bb58);
        iVar6 = _wtoi((wchar_t *)(piVar8 + 4));
        puVar9 = FUN_00412bd0(&local_28,iVar6,iVar13);
        local_8._0_1_ = 5;
        FUN_00405aa0(&local_14,puVar9);
        local_8._0_1_ = 4;
        LOCK();
        piVar8 = (int *)(local_28 + -4);
        iVar13 = *piVar8;
        *piVar8 = *piVar8 + -1;
        UNLOCK();
        if (iVar13 == 1 || iVar13 + -1 < 0) {
          (**(code **)(**(int **)(local_28 + -0x10) + 4))();
        }
        pwVar5 = local_14;
        YJXUI::MComboBox::AddItem(*(MComboBox **)(local_20 + 0x344),local_14,*local_2c,0);
        local_8 = (uint)local_8._1_3_ << 8;
        LOCK();
        pwVar1 = pwVar5 + -2;
        iVar13 = *(int *)pwVar1;
        *(int *)pwVar1 = *(int *)pwVar1 + -1;
        UNLOCK();
        uVar10 = local_18;
        if (iVar13 == 1 || iVar13 + -1 < 0) {
          (**(code **)(**(int **)(pwVar5 + -8) + 4))();
          uVar10 = local_18;
        }
      }
      uVar12 = uVar12 + 1;
    } while ((int)uVar12 < local_1c);
  }
  puVar9 = (undefined4 *)0x0;
  if (0 < local_1c) {
    puVar11 = (undefined4 *)((int)local_38 - (int)pvVar3 >> 2);
    iVar13 = local_1c;
    local_2c = puVar11;
    do {
      if (puVar11 <= puVar9) {
LAB_00426591:
                    /* WARNING: Subroutine does not return */
        std::_Xout_of_range("invalid vector<T> subscript");
      }
      pvVar2 = *(void **)((int)pvVar3 + (int)puVar9 * 4);
      if (pvVar2 != (void *)0x0) {
        iVar6 = *(int *)((int)pvVar2 + 8);
        LOCK();
        piVar8 = (int *)(iVar6 + -4);
        iVar13 = *piVar8;
        *piVar8 = *piVar8 + -1;
        UNLOCK();
        if (iVar13 + -1 < 1) {
          (**(code **)(**(int **)(iVar6 + -0x10) + 4))();
        }
        iVar6 = *(int *)((int)pvVar2 + 4);
        LOCK();
        piVar8 = (int *)(iVar6 + -4);
        iVar13 = *piVar8;
        *piVar8 = *piVar8 + -1;
        UNLOCK();
        if (iVar13 == 1 || iVar13 + -1 < 0) {
          (**(code **)(**(int **)(iVar6 + -0x10) + 4))();
        }
        FUN_004484a6(pvVar2);
        iVar13 = local_1c;
        puVar11 = local_2c;
      }
      puVar9 = (undefined4 *)((int)puVar9 + 1);
    } while ((int)puVar9 < iVar13);
  }
  local_38 = pvVar3;
  if ((*(int *)(local_24 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1))
  {
    local_8 = CONCAT31(local_8._1_3_,6);
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    FUN_00448621(&DAT_0056ef90);
  }
  local_30 = &DAT_0056ef28;
  EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0056ef28);
  local_8._0_1_ = 7;
  iVar13 = 0;
  FUN_00447f90(local_48);
  local_8 = CONCAT31(local_8._1_3_,8);
  FUN_004483f0(&DAT_0056ef20,(int)local_48,
               (byte *)"SELECT profile FROM t_profile_data WHERE status = ?",(byte *)0xffffffff);
  FUN_00448190(local_48,1,1);
  uVar12 = FUN_004482e0((int)local_48);
  if (uVar12 == 100) {
    iVar13 = FUN_00448270(local_48,0);
  }
  FUN_00448030(local_48);
  local_8 = local_8 & 0xffffff00;
  LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0056ef28);
  iVar4 = local_20;
  iVar6 = local_24;
  *(int *)(local_20 + 0x6f0) = iVar13;
  if (iVar13 < 1) {
    if ((*(int *)(local_24 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)
       ) {
      local_8._0_1_ = 9;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8 = (uint)local_8._1_3_ << 8;
      FUN_00448621(&DAT_0056ef90);
    }
    FUN_004044b0(&DAT_0056ef20,1);
    if ((*(int *)(iVar6 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8 = CONCAT31(local_8._1_3_,10);
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      FUN_00448621(&DAT_0056ef90);
    }
    local_30 = &DAT_0056ef28;
    EnterCriticalSection((LPCRITICAL_SECTION)&DAT_0056ef28);
    local_8._0_1_ = 0xb;
    uVar14 = 0;
    FUN_00447f90(local_48);
    local_8 = CONCAT31(local_8._1_3_,0xc);
    FUN_004483f0(&DAT_0056ef20,(int)local_48,
                 (byte *)"SELECT profile FROM t_profile_data WHERE status = ?",(byte *)0xffffffff);
    FUN_00448190(local_48,1,1);
    uVar12 = FUN_004482e0((int)local_48);
    if (uVar12 == 100) {
      uVar14 = FUN_00448270(local_48,0);
    }
    FUN_00448030(local_48);
    local_8 = local_8 & 0xffffff00;
    LeaveCriticalSection((LPCRITICAL_SECTION)&DAT_0056ef28);
    *(undefined4 *)(iVar4 + 0x6f0) = uVar14;
  }
  YJXUI::MComboBox::SelectData(*(MComboBox **)(iVar4 + 0x344),*(long *)(iVar4 + 0x6f0));
  if (pvVar3 != (void *)0x0) {
    FUN_00406040(pvVar3,local_34 - (int)pvVar3 >> 2);
  }
  ExceptionList = local_10;
  return;
}

