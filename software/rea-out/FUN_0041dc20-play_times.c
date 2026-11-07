
void __fastcall FUN_0041dc20(MWindow *param_1)

{
  LPCWSTR pWVar1;
  short sVar2;
  char cVar3;
  HWND pHVar4;
  int iVar5;
  BOOL BVar6;
  uint uVar7;
  short *psVar8;
  wchar_t *pwVar9;
  undefined *puVar10;
  undefined1 *puVar11;
  int *piVar12;
  short *psVar13;
  int *piVar14;
  undefined4 uVar15;
  int in_stack_fffffa84;
  int iVar16;
  int iVar17;
  int iVar18;
  int iVar19;
  int iVar20;
  undefined4 local_558;
  wchar_t *local_554;
  int local_550;
  int local_54c;
  int local_548;
  int local_544;
  undefined1 *local_540;
  MWindow *local_53c;
  undefined4 local_538;
  int iStack_534;
  int iStack_530;
  int iStack_52c;
  int local_528;
  int local_524;
  int local_520;
  LPCWSTR local_51c;
  undefined1 *local_518;
  undefined1 *local_514;
  undefined **local_510 [5];
  int *local_4fc;
  short local_294 [260];
  undefined4 local_8c [6];
  int local_74 [14];
  byte local_3c [16];
  void *local_2c [5];
  uint local_18;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00535108;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_53c = param_1;
  YJXUI::MWindow::GetSafeHwnd(param_1);
  uVar15 = 1;
  FUN_00421310(local_510,1);
  local_510[0] = WTL::CFileDialog::vftable;
  local_8 = 0;
  pHVar4 = GetActiveWindow();
  iVar5 = FUN_00421240(local_510,pHVar4);
  if (iVar5 != 2) {
    FUN_004054f0(&local_51c,local_294);
    local_8._0_1_ = 1;
    BVar6 = PathFileExistsW(local_51c);
    if (BVar6 != 0) {
      FUN_0040e170(local_8c);
      local_8._0_1_ = 2;
      if ((int)(*(uint *)(local_51c + -4) | 1U - *(int *)(local_51c + -2)) < 0) {
        FUN_00405e50(&local_51c,0);
      }
      if ((local_3c[0] & 0x30) == 0) {
        iVar5 = 0x41dd26;
        cVar3 = FUN_00443e20(local_8c,local_74,local_51c,(uint *)local_3c);
        if (((cVar3 != '\0') && (uVar7 = FUN_00444e10(local_8c), (char)uVar7 != '\0')) &&
           (uVar7 = FUN_00444230(local_8c,L"macro"), (char)uVar7 != '\0')) {
          FUN_00444d70((int)local_8c);
          FUN_00444230(local_8c,L"macroinfo");
          FUN_00407e20(&local_558);
          local_8._0_1_ = 3;
          psVar8 = (short *)FUN_0040e250(local_8c,local_2c,L"macro_name");
          local_8._0_1_ = 4;
          if (7 < *(uint *)(psVar8 + 10)) {
            psVar8 = *(short **)psVar8;
          }
          FUN_004053e0(&local_554,psVar8);
          local_8._0_1_ = 3;
          FUN_00409e30(local_2c);
          pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"macro_type");
          if (7 < *(uint *)(pwVar9 + 10)) {
            pwVar9 = *(wchar_t **)pwVar9;
          }
          local_550 = _wtoi(pwVar9);
          FUN_00409e30(local_2c);
          pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"play_times");
          if (7 < *(uint *)(pwVar9 + 10)) {
            pwVar9 = *(wchar_t **)pwVar9;
          }
          local_54c = _wtoi(pwVar9);
          FUN_00409e30(local_2c);
          pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"delay_type");
          if (7 < *(uint *)(pwVar9 + 10)) {
            pwVar9 = *(wchar_t **)pwVar9;
          }
          local_548 = _wtoi(pwVar9);
          FUN_00409e30(local_2c);
          iVar18 = 0x41de84;
          pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"delay_time");
          if (7 < *(uint *)(pwVar9 + 10)) {
            pwVar9 = *(wchar_t **)pwVar9;
          }
          iVar19 = 0x41de8f;
          local_544 = _wtoi(pwVar9);
          iVar20 = 0x41dea0;
          FUN_00409e30(local_2c);
          local_514 = &stack0xfffffa80;
          FUN_0041dbd0(&stack0xfffffa80,&local_558);
          local_8._0_1_ = 5;
          puVar10 = FUN_00401170();
          local_8._0_1_ = 3;
          puVar11 = (undefined1 *)
                    FUN_00408010(puVar10,uVar15,in_stack_fffffa84,iVar5,iVar18,iVar19,iVar20);
          local_514 = puVar11;
          if ((0 < (int)puVar11) &&
             (uVar7 = FUN_00444230(local_8c,L"macroitems"), (char)uVar7 != '\0')) {
            FUN_00444d70((int)local_8c);
            while (uVar7 = FUN_00444230(local_8c,L"item"), (char)uVar7 != '\0') {
              piVar12 = (int *)FUN_00406b10();
              if (piVar12 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
                FUN_00406bc0(0x80004005);
              }
              local_520 = (**(code **)(*piVar12 + 0xc))();
              local_520 = local_520 + 0x10;
              local_8._0_1_ = 6;
              local_528 = 0;
              local_538 = 0;
              iStack_534 = 0;
              iStack_530 = 0;
              iStack_52c = 0;
              FUN_00405eb0(&local_520,&PTR_0054b37c,0);
              local_524 = 0;
              local_8._0_1_ = 7;
              iStack_52c = 0;
              iStack_534 = (int)puVar11;
              psVar8 = (short *)FUN_0040e250(local_8c,local_2c,L"desc");
              local_8._0_1_ = 8;
              if (7 < *(uint *)(psVar8 + 10)) {
                psVar8 = *(short **)psVar8;
              }
              if (psVar8 == (short *)0x0) {
                iVar5 = 0;
              }
              else {
                psVar13 = psVar8;
                do {
                  sVar2 = *psVar13;
                  psVar13 = psVar13 + 1;
                } while (sVar2 != 0);
                iVar5 = (int)psVar13 - (int)(psVar8 + 1) >> 1;
              }
              FUN_00405eb0(&local_520,psVar8,iVar5);
              local_8 = CONCAT31(local_8._1_3_,7);
              if (7 < local_18) {
                FUN_0040a470(local_2c[0],local_18 + 1);
              }
              pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"index");
              if (7 < *(uint *)(pwVar9 + 10)) {
                pwVar9 = *(wchar_t **)pwVar9;
              }
              iStack_52c = _wtoi(pwVar9);
              if (7 < local_18) {
                FUN_0040a470(local_2c[0],local_18 + 1);
              }
              pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"type");
              if (7 < *(uint *)(pwVar9 + 10)) {
                pwVar9 = *(wchar_t **)pwVar9;
              }
              iStack_530 = _wtoi(pwVar9);
              if (7 < local_18) {
                FUN_0040a470(local_2c[0],local_18 + 1);
              }
              pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"value");
              if (7 < *(uint *)(pwVar9 + 10)) {
                pwVar9 = *(wchar_t **)pwVar9;
              }
              iVar5 = _wtoi(pwVar9);
              local_528 = iVar5;
              if (7 < local_18) {
                FUN_0040a470(local_2c[0],local_18 + 1);
              }
              pwVar9 = (wchar_t *)FUN_0040e250(local_8c,local_2c,L"timestamp");
              if (7 < *(uint *)(pwVar9 + 10)) {
                pwVar9 = *(wchar_t **)pwVar9;
              }
              iVar18 = _wtoi(pwVar9);
              local_524 = iVar18;
              if (7 < local_18) {
                FUN_0040a470(local_2c[0],local_18 + 1);
              }
              iVar19 = local_520;
              local_518 = &stack0xfffffa7c;
              piVar14 = (int *)(local_520 + -0x10);
              local_540 = &stack0xfffffa94;
              uVar15 = local_538;
              iVar20 = iStack_534;
              iVar16 = iStack_530;
              iVar17 = iStack_52c;
              piVar12 = FUN_00405df0(piVar14);
              piVar12 = piVar12 + 4;
              local_8._0_1_ = 9;
              puVar10 = FUN_00401170();
              local_8._0_1_ = 7;
              FUN_004088b0(puVar10,uVar15,iVar20,iVar16,iVar17,iVar5,iVar18,(int)piVar12);
              puVar11 = local_514;
              local_8._0_1_ = 3;
              LOCK();
              piVar12 = (int *)(iVar19 + -4);
              iVar5 = *piVar12;
              *piVar12 = *piVar12 + -1;
              UNLOCK();
              if (iVar5 == 1 || iVar5 + -1 < 0) {
                (**(code **)(*(int *)*piVar14 + 4))();
              }
            }
            FUN_00444db0((int)local_8c);
          }
          YJXUI::MacroList::AddString(*(MacroList **)(local_53c + 0x4a0),local_554,(long)puVar11,-1)
          ;
          local_8._0_1_ = 2;
          LOCK();
          pwVar9 = local_554 + -2;
          iVar5 = *(int *)pwVar9;
          *(int *)pwVar9 = *(int *)pwVar9 + -1;
          UNLOCK();
          if (iVar5 == 1 || iVar5 + -1 < 0) {
            (**(code **)(**(int **)(local_554 + -8) + 4))();
          }
        }
      }
      FUN_00443c50(local_8c);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    LOCK();
    pWVar1 = local_51c + -2;
    iVar5 = *(int *)pWVar1;
    *(int *)pWVar1 = *(int *)pWVar1 + -1;
    UNLOCK();
    if (iVar5 == 1 || iVar5 + -1 < 0) {
      (**(code **)(**(int **)(local_51c + -8) + 4))();
    }
  }
  if (local_4fc != (int *)0x0) {
    FUN_00447dcb(local_4fc);
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

