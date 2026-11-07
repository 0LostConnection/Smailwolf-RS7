
void __thiscall FUN_00427b40(void *this,int param_1)

{
  wchar_t *pwVar1;
  void *pvVar2;
  int iVar3;
  int *piVar4;
  HWND pHVar5;
  int iVar6;
  int *piVar7;
  undefined *this_00;
  wchar_t *extraout_ECX;
  wchar_t *pwVar8;
  wchar_t *pwVar9;
  int *extraout_ECX_00;
  int *extraout_ECX_01;
  int *extraout_ECX_02;
  int *extraout_ECX_03;
  int *extraout_ECX_04;
  int *extraout_ECX_05;
  int *extraout_ECX_06;
  int *extraout_ECX_07;
  int *extraout_ECX_08;
  int *extraout_ECX_09;
  int *extraout_ECX_10;
  int *extraout_ECX_11;
  int *extraout_ECX_12;
  int *extraout_ECX_13;
  wchar_t *extraout_ECX_14;
  int *extraout_ECX_15;
  int *extraout_ECX_16;
  int *extraout_ECX_17;
  int *extraout_ECX_18;
  int *extraout_ECX_19;
  int *extraout_ECX_20;
  void *pvVar10;
  wchar_t *pwVar11;
  void *unaff_EDI;
  bool bVar12;
  void **ppvVar13;
  wchar_t **ppwVar14;
  void *local_534;
  int local_530;
  int local_52c;
  int local_528;
  void *local_524;
  void *local_520;
  int local_51c;
  wchar_t *local_518;
  wchar_t *local_514;
  wchar_t *local_510;
  wchar_t *local_50c;
  wchar_t *local_508;
  wchar_t *local_504;
  undefined **local_500 [5];
  int *local_4ec;
  short local_284 [262];
  undefined4 local_78 [6];
  int local_60 [6];
  wchar_t *local_48;
  wchar_t *local_44;
  wchar_t *local_40;
  uint local_34;
  undefined4 local_30;
  undefined4 local_2c;
  byte local_28 [12];
  int *local_1c;
  int *local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005360d2;
  local_10 = ExceptionList;
  piVar4 = (int *)(DAT_0055f00c ^ (uint)&stack0xfffffffc);
  ExceptionList = &local_10;
  local_50c = this;
  local_18 = piVar4;
  YJXUI::MWindow::GetSafeHwnd(this);
  FUN_00421310(local_500,0);
  local_500[0] = WTL::CFileDialog::vftable;
  local_8 = 0;
  pHVar5 = GetActiveWindow();
  iVar6 = FUN_00421240(local_500,pHVar5);
  if (iVar6 != 2) {
    FUN_004054f0(&local_528,local_284);
    local_8._0_1_ = 1;
    YJXUI::MControlFont::GetTitle(*(MControlFont **)((int)this + 0x344));
    local_8._0_1_ = 2;
    piVar7 = (int *)FUN_00406b10();
    if (piVar7 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00406bc0(0x80004005);
    }
    iVar6 = (**(code **)(*piVar7 + 0xc))();
    pwVar11 = (wchar_t *)(iVar6 + 0x10);
    local_8._0_1_ = 3;
    local_508 = pwVar11;
    FUN_0040e170(local_78);
    local_8 = CONCAT31(local_8._1_3_,4);
    FUN_00443d30(local_78,(int *)L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
    FUN_00446570(local_78,(int *)L"profile",(wchar_t *)0x0,0);
    if ((local_44 != (wchar_t *)0x0) && (local_34 == 1)) {
      local_48 = local_44;
      bVar12 = local_40 != (wchar_t *)0x0;
      local_44 = local_40;
      local_40 = (wchar_t *)0x0;
      local_34 = (uint)bVar12;
      local_30 = 0;
      local_2c = 0;
    }
    FUN_00446570(local_78,(int *)L"profileinfo",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_518 + -4) | 1U - *(int *)(local_518 + -2)) < 0) {
      FUN_00405e50(&local_518,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"name",local_518,0);
    if ((local_44 != (wchar_t *)0x0) && (local_34 == 1)) {
      local_48 = local_44;
      bVar12 = local_40 != (wchar_t *)0x0;
      local_44 = local_40;
      local_40 = (wchar_t *)0x0;
      local_34 = (uint)bVar12;
      local_30 = 0;
      local_2c = 0;
    }
    FUN_00446570(local_78,(int *)L"keyitems",(wchar_t *)0x0,0);
    pwVar9 = local_40;
    pwVar8 = extraout_ECX;
    if ((local_44 != (wchar_t *)0x0) && (pwVar8 = extraout_ECX, local_34 == 1)) {
      local_48 = local_44;
      bVar12 = local_40 != (wchar_t *)0x0;
      local_44 = local_40;
      local_40 = (wchar_t *)0x0;
      local_34 = (uint)bVar12;
      local_30 = 0;
      local_2c = 0;
      pwVar8 = pwVar9;
    }
    local_524 = (void *)0x0;
    local_520 = (void *)0x0;
    local_51c = 0;
    ppvVar13 = &local_524;
    local_8._0_1_ = 5;
    this_00 = FUN_00401170();
    iVar6 = FUN_00407320(this_00,param_1,pwVar8,(int *)ppvVar13);
    pvVar10 = local_520;
    if (0 < iVar6) {
      pwVar9 = (wchar_t *)((int)local_520 - (int)local_524 >> 2);
      local_504 = (wchar_t *)0x0;
      pvVar10 = local_524;
      if (pwVar9 != (wchar_t *)0x0) {
        pvVar10 = local_524;
        local_514 = pwVar9;
        if (pwVar9 == (wchar_t *)0x0) {
LAB_0042851b:
                    /* WARNING: Subroutine does not return */
          std::_Xout_of_range("invalid vector<T> subscript");
        }
        do {
          pvVar2 = *(void **)((int)pvVar10 + (int)local_504 * 4);
          if (pvVar2 != (void *)0x0) {
            FUN_00446570(local_78,(int *)L"item",(wchar_t *)0x0,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"key_code",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"macro_type",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"macro_value",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"macro_value2",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            pwVar11 = local_508;
            FUN_00445a00(local_78,(uint)local_44,L"macro_value3",local_508,0);
            if ((int)(*(uint *)(*(int *)((int)pvVar2 + 0x28) + -8) |
                     1U - *(int *)(*(int *)((int)pvVar2 + 0x28) + -4)) < 0) {
              FUN_00405e50((void *)((int)pvVar2 + 0x28),0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"macro_desc",*(wchar_t **)((int)pvVar2 + 0x28),0);
            iVar3 = *(int *)((int)pvVar2 + 0x28);
            LOCK();
            piVar7 = (int *)(iVar3 + -4);
            iVar6 = *piVar7;
            *piVar7 = *piVar7 + -1;
            UNLOCK();
            if (iVar6 + -1 < 1) {
              (**(code **)(**(int **)(iVar3 + -0x10) + 4))();
            }
            iVar3 = *(int *)((int)pvVar2 + 0x14);
            LOCK();
            piVar7 = (int *)(iVar3 + -4);
            iVar6 = *piVar7;
            *piVar7 = *piVar7 + -1;
            UNLOCK();
            if (iVar6 == 1 || iVar6 + -1 < 0) {
              (**(code **)(**(int **)(iVar3 + -0x10) + 4))();
            }
            FUN_004484a6(pvVar2);
            pwVar9 = local_514;
            pvVar10 = local_524;
          }
          local_504 = (wchar_t *)((int)local_504 + 1);
        } while (local_504 < pwVar9);
      }
    }
    local_520 = pvVar10;
    pwVar9 = local_44;
    local_514 = local_48;
    if (local_48 != (wchar_t *)0x0) {
      local_44 = local_48;
      local_40 = pwVar9;
      local_34 = (uint)(local_48 != (wchar_t *)0x0);
      local_30 = 0;
      local_2c = 0;
      local_48 = *(wchar_t **)
                  (*(int *)(*local_1c + ((int)local_48 >> 0x10) * 4) + 0x10 +
                  ((uint)local_48 & 0xffff) * 0x20);
    }
    if (*(int *)(local_50c + 0x38c) != 0) {
      FUN_00446570(local_78,(int *)L"Lightitems",(wchar_t *)0x0,0);
      iVar6 = *(int *)ThreadLocalStoragePointer;
      if ((*(int *)(iVar6 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1))
      {
        local_8._0_1_ = 6;
        FUN_00401290();
        _atexit(thunk_FUN_004013b0);
        local_8._0_1_ = 5;
        piVar4 = &DAT_0056ef90;
        FUN_00448621(&DAT_0056ef90);
      }
      FUN_00407930(&DAT_0056ef20,*(int *)(local_50c + 0x378));
      FUN_00406540(&local_508,0x54a358);
      if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
        FUN_00405e50(&local_508,0);
      }
      pwVar11 = local_508;
      FUN_00445a00(local_78,(uint)local_44,L"light_mode",local_508,0);
      if ((local_44 != (wchar_t *)0x0) && (local_34 == 1)) {
        local_48 = local_44;
        bVar12 = local_40 != (wchar_t *)0x0;
        local_44 = local_40;
        local_40 = (wchar_t *)0x0;
        local_34 = (uint)bVar12;
        local_30 = 0;
        local_2c = 0;
      }
      local_534 = (void *)0x0;
      local_530 = 0;
      local_52c = 0;
      local_8._0_1_ = 7;
      if ((*(int *)(iVar6 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1))
      {
        local_8._0_1_ = 8;
        FUN_00401290();
        _atexit(thunk_FUN_004013b0);
        local_8._0_1_ = 7;
        piVar4 = &DAT_0056ef90;
        FUN_00448621(&DAT_0056ef90);
      }
      local_510 = (wchar_t *)
                  FUN_00407b90(&DAT_0056ef20,*(undefined4 **)(local_50c + 0x378),(int *)&local_534);
      local_504 = (wchar_t *)0x0;
      if (0 < (int)local_510) {
        pwVar9 = (wchar_t *)(local_530 - (int)local_534 >> 2);
        pvVar10 = local_534;
        local_514 = pwVar9;
        do {
          if (pwVar9 <= local_504) goto LAB_0042851b;
          pvVar2 = *(void **)((int)pvVar10 + (int)local_504 * 4);
          if (pvVar2 != (void *)0x0) {
            FUN_00446570(local_78,(int *)L"item",(wchar_t *)0x0,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"light_mode",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"brightness",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"speed",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"direction",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"colorful",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            FUN_00445a00(local_78,(uint)local_44,L"colorindex",local_508,0);
            FUN_00406540(&local_508,0x54a358);
            if ((int)(*(uint *)(local_508 + -4) | 1U - *(int *)(local_508 + -2)) < 0) {
              FUN_00405e50(&local_508,0);
            }
            pwVar11 = local_508;
            FUN_00445a00(local_78,(uint)local_44,L"color_value",local_508,0);
            iVar3 = *(int *)((int)pvVar2 + 8);
            LOCK();
            piVar7 = (int *)(iVar3 + -4);
            iVar6 = *piVar7;
            *piVar7 = *piVar7 + -1;
            UNLOCK();
            if (iVar6 == 1 || iVar6 + -1 < 0) {
              (**(code **)(**(int **)(iVar3 + -0x10) + 4))();
            }
            FUN_004484a6(pvVar2);
            pwVar9 = local_514;
            pvVar10 = local_534;
          }
          local_504 = (wchar_t *)((int)local_504 + 1);
        } while ((int)local_504 < (int)local_510);
      }
      pwVar9 = local_44;
      local_510 = local_48;
      if (local_48 != (wchar_t *)0x0) {
        local_44 = local_48;
        local_40 = pwVar9;
        local_34 = (uint)(local_48 != (wchar_t *)0x0);
        local_30 = 0;
        local_2c = 0;
        local_48 = *(wchar_t **)
                    (*(int *)(*local_1c + ((int)local_48 >> 0x10) * 4) + 0x10 +
                    ((uint)local_48 & 0xffff) * 0x20);
      }
      local_8._0_1_ = 5;
      if (local_534 != (void *)0x0) {
        FUN_00406040(local_534,local_52c - (int)local_534 >> 2);
      }
    }
    piVar7 = (int *)FUN_00406b10();
    if (piVar7 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00406bc0(0x80004005);
    }
    iVar6 = (**(code **)(*piVar7 + 0xc))();
    local_504 = (wchar_t *)(iVar6 + 0x10);
    local_8._0_1_ = 9;
    FUN_00446570(local_78,(int *)L"Mouse_DPI",(wchar_t *)0x0,0);
    local_510 = (wchar_t *)&stack0xfffffab0;
    FUN_004054f0(&stack0xfffffab0,L"dpi_flag");
    local_8._0_1_ = 10;
    pwVar9 = *(wchar_t **)ThreadLocalStoragePointer;
    local_514 = pwVar9;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0xb;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 10;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,unaff_EDI);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"dpi_flag",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_00;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_index");
    local_8._0_1_ = 0xc;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0xd;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0xc;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"dpi_index",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_01;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_count");
    local_8._0_1_ = 0xe;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0xf;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0xe;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"dpi_count",local_504,0);
    if ((local_44 != (wchar_t *)0x0) && (local_34 == 1)) {
      local_48 = local_44;
      bVar12 = local_40 != (wchar_t *)0x0;
      local_44 = local_40;
      local_40 = (wchar_t *)0x0;
      local_34 = (uint)bVar12;
      local_30 = 0;
      local_2c = 0;
    }
    FUN_00446570(local_78,(int *)L"DPI1",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_02;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group0_value");
    local_8._0_1_ = 0x10;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x11;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x10;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_03;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group0_rgb");
    local_8._0_1_ = 0x12;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x13;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x12;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    FUN_00446570(local_78,(int *)L"DPI2",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_04;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group1_value");
    local_8._0_1_ = 0x14;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x15;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x14;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_05;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group1_rgb");
    local_8._0_1_ = 0x16;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x17;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x16;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    FUN_00446570(local_78,(int *)L"DPI3",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_06;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group2_value");
    local_8._0_1_ = 0x18;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x19;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x18;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_07;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group2_rgb");
    local_8._0_1_ = 0x1a;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x1b;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1a;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    FUN_00446570(local_78,(int *)L"DPI4",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_08;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group3_value");
    local_8._0_1_ = 0x1c;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x1d;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1c;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_09;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group3_rgb");
    local_8._0_1_ = 0x1e;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x1f;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x1e;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    FUN_00446570(local_78,(int *)L"DPI5",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_10;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group4_value");
    local_8._0_1_ = 0x20;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x21;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x20;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_11;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group4_rgb");
    local_8._0_1_ = 0x22;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x23;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x22;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    FUN_00446570(local_78,(int *)L"DPI6",(wchar_t *)0x0,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_12;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group5_value");
    local_8._0_1_ = 0x24;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x25;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x24;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_13;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"dpi_group5_rgb");
    local_8._0_1_ = 0x26;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x27;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x26;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"color",local_504,0);
    local_510 = local_48;
    if (local_48 != (wchar_t *)0x0) {
      local_40 = local_44;
      local_34 = (uint)(local_48 != (wchar_t *)0x0);
      local_44 = local_48;
      local_30 = 0;
      local_2c = 0;
      pwVar9 = local_514;
      local_48 = *(wchar_t **)
                  (*(int *)(*local_1c + ((int)local_48 >> 0x10) * 4) + 0x10 +
                  ((uint)local_48 & 0xffff) * 0x20);
    }
    FUN_00446570(local_78,(int *)L"Mouse",(wchar_t *)0x0,0);
    pwVar8 = local_40;
    piVar4 = (int *)extraout_ECX_14;
    if ((local_44 != (wchar_t *)0x0) && (piVar4 = (int *)extraout_ECX_14, local_34 == 1)) {
      local_48 = local_44;
      bVar12 = local_40 != (wchar_t *)0x0;
      local_44 = local_40;
      local_40 = (wchar_t *)0x0;
      local_34 = (uint)bVar12;
      local_30 = 0;
      local_2c = 0;
      piVar4 = (int *)pwVar8;
    }
    ppwVar14 = &local_504;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"button_respondtime");
    local_8._0_1_ = 0x28;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x29;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x28;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"button_respondtime",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_15;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"report_rate");
    local_8._0_1_ = 0x2a;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x2b;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x2a;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"report_rate",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_16;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"sensor_flag");
    local_8._0_1_ = 0x2c;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x2d;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x2c;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"sensor_flag",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_17;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"liftoff_height");
    local_8._0_1_ = 0x2e;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x2f;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x2e;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"liftoff_height",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_18;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"scroll_flag");
    local_8._0_1_ = 0x30;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x31;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x30;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"scroll_flag",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_19;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"e-sports_flag");
    local_8._0_1_ = 0x32;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x33;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x32;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"e-sports_flag",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    ppwVar14 = &local_504;
    piVar4 = extraout_ECX_20;
    local_510 = (wchar_t *)&stack0xfffffab8;
    FUN_004054f0(&stack0xfffffab8,L"leftbtn_lock");
    local_8._0_1_ = 0x34;
    if ((*(int *)((int)pwVar9 + 4) < DAT_0056ef90) &&
       (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
      local_8._0_1_ = 0x35;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 0x34;
      piVar4 = &DAT_0056ef90;
      FUN_00448621(&DAT_0056ef90);
    }
    local_8 = CONCAT31(local_8._1_3_,9);
    FUN_00401a10(&DAT_0056ef20,*(int *)(local_50c + 0x378),(int)piVar4,ppwVar14);
    FUN_00446570(local_78,(int *)L"leftbtn_lock",(wchar_t *)0x0,0);
    if ((int)(*(uint *)(local_504 + -4) | 1U - *(int *)(local_504 + -2)) < 0) {
      FUN_00405e50(&local_504,0);
    }
    pwVar9 = local_504;
    FUN_00445a00(local_78,(uint)local_44,L"value",local_504,0);
    pwVar8 = local_44;
    local_510 = local_48;
    if (local_48 != (wchar_t *)0x0) {
      local_44 = local_48;
      local_40 = pwVar8;
      local_34 = (uint)(local_48 != (wchar_t *)0x0);
      local_30 = 0;
      local_2c = 0;
      local_48 = *(wchar_t **)
                  (*(int *)(*local_1c + ((int)local_48 >> 0x10) * 4) + 0x10 +
                  ((uint)local_48 & 0xffff) * 0x20);
    }
    piVar4 = (int *)FUN_00406b10();
    if (piVar4 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
      FUN_00406bc0(0x80004005);
    }
    iVar6 = (**(code **)(*piVar4 + 0xc))();
    local_50c = (wchar_t *)(iVar6 + 0x10);
    local_8 = CONCAT31(local_8._1_3_,0x36);
    FUN_00406540(&local_50c,0x54d410);
    if ((int)(*(uint *)(local_50c + -4) | 1U - *(int *)(local_50c + -2)) < 0) {
      FUN_00405e50(&local_50c,0);
    }
    pwVar8 = local_50c;
    if ((local_28[0] & 0x30) == 0) {
      FUN_004440a0(local_78,local_60,local_50c,(uint *)local_28);
    }
    local_8._0_1_ = 9;
    LOCK();
    pwVar1 = pwVar8 + -2;
    iVar6 = *(int *)pwVar1;
    *(int *)pwVar1 = *(int *)pwVar1 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(pwVar8 + -8) + 4))();
    }
    local_8 = CONCAT31(local_8._1_3_,5);
    LOCK();
    pwVar8 = pwVar9 + -2;
    iVar6 = *(int *)pwVar8;
    *(int *)pwVar8 = *(int *)pwVar8 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(pwVar9 + -8) + 4))();
    }
    if (local_524 != (void *)0x0) {
      FUN_00406040(local_524,local_51c - (int)local_524 >> 2);
    }
    FUN_00443c50(local_78);
    local_8._0_1_ = 2;
    LOCK();
    pwVar9 = pwVar11 + -2;
    iVar6 = *(int *)pwVar9;
    *(int *)pwVar9 = *(int *)pwVar9 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(pwVar11 + -8) + 4))();
    }
    local_8._0_1_ = 1;
    LOCK();
    pwVar11 = local_518 + -2;
    iVar6 = *(int *)pwVar11;
    *(int *)pwVar11 = *(int *)pwVar11 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(local_518 + -8) + 4))();
    }
    local_8 = (uint)local_8._1_3_ << 8;
    LOCK();
    piVar4 = (int *)(local_528 + -4);
    iVar6 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar6 == 1 || iVar6 + -1 < 0) {
      (**(code **)(**(int **)(local_528 + -0x10) + 4))();
    }
  }
  if (local_4ec != (int *)0x0) {
    FUN_00447dcb(local_4ec);
  }
  ExceptionList = local_10;
  __security_check_cookie((uint)local_18 ^ (uint)&stack0xfffffffc);
  return;
}

