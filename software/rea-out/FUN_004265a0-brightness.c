
void __fastcall FUN_004265a0(MWindow *param_1)

{
  LPCWSTR pWVar1;
  short sVar2;
  char cVar3;
  HWND pHVar4;
  int iVar5;
  BOOL BVar6;
  uint uVar7;
  short *psVar8;
  undefined *puVar9;
  wchar_t *pwVar10;
  int iVar11;
  int *piVar12;
  short *psVar13;
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
  int extraout_ECX_16;
  int extraout_ECX_17;
  int extraout_ECX_18;
  int extraout_ECX_19;
  int extraout_ECX_20;
  int iVar14;
  undefined4 *puVar15;
  undefined4 local_578 [2];
  int local_570;
  undefined4 local_56c;
  int local_568;
  int local_564;
  int local_560;
  int local_55c;
  int local_558;
  int local_554;
  int local_550;
  int local_54c;
  int local_548;
  int local_544;
  LPCWSTR local_540;
  int local_53c;
  undefined1 *local_538;
  undefined1 *local_534;
  undefined **local_530 [5];
  int *local_51c;
  short local_2b4 [262];
  undefined4 local_a8 [6];
  undefined4 local_90 [6];
  int local_78 [14];
  byte local_40 [16];
  void *local_30 [5];
  uint local_1c;
  uint local_18;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00535e34;
  local_10 = ExceptionList;
  local_18 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  YJXUI::MWindow::GetSafeHwnd(param_1);
  FUN_00421310(local_530,1);
  local_530[0] = WTL::CFileDialog::vftable;
  local_8 = 0;
  pHVar4 = GetActiveWindow();
  iVar5 = FUN_00421240(local_530,pHVar4);
  if (iVar5 != 2) {
    FUN_004054f0(&local_540,local_2b4);
    local_8._0_1_ = 1;
    BVar6 = PathFileExistsW(local_540);
    if (BVar6 != 0) {
      FUN_0040e170(local_90);
      local_8._0_1_ = 2;
      if ((int)(*(uint *)(local_540 + -4) | 1U - *(int *)(local_540 + -2)) < 0) {
        FUN_00405e50(&local_540,0);
      }
      if (((((local_40[0] & 0x30) == 0) &&
           (cVar3 = FUN_00443e20(local_90,local_78,local_540,(uint *)local_40), cVar3 != '\0')) &&
          (uVar7 = FUN_00444e10(local_90), (char)uVar7 != '\0')) &&
         (uVar7 = FUN_00444230(local_90,L"profile"), (char)uVar7 != '\0')) {
        FUN_00444d70((int)local_90);
        FUN_00444230(local_90,L"profileinfo");
        psVar8 = (short *)FUN_0040e250(local_90,local_a8,L"name");
        local_8._0_1_ = 3;
        if (7 < *(uint *)(psVar8 + 10)) {
          psVar8 = *(short **)psVar8;
        }
        FUN_004054f0(&local_544,psVar8);
        local_8 = CONCAT31(local_8._1_3_,5);
        FUN_00409e30(local_a8);
        FUN_00444d70((int)local_90);
        iVar5 = *(int *)(param_1 + 0x6f0);
        puVar9 = FUN_00401170();
        FUN_004075a0(puVar9,iVar5);
        uVar7 = FUN_00444230(local_90,L"keyitems");
        if ((char)uVar7 != '\0') {
          FUN_00444d70((int)local_90);
          while (uVar7 = FUN_00444230(local_90,L"item"), (char)uVar7 != '\0') {
            FUN_00406c90(&local_570);
            local_8 = CONCAT31(local_8._1_3_,6);
            local_56c = *(undefined4 *)(param_1 + 0x6f0);
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"key_code");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            local_564 = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"macro_type");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            local_558 = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"macro_value");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            local_554 = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"macro_value2");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            local_550 = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"macro_value3");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            local_54c = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"macro_desc");
            local_8._0_1_ = 7;
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
            FUN_00405eb0(&local_548,psVar8,iVar5);
            local_8._0_1_ = 6;
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            piVar12 = &local_570;
            puVar9 = FUN_00401170();
            FUN_00406d80(puVar9,(int)piVar12);
            local_8 = CONCAT31(local_8._1_3_,5);
            LOCK();
            piVar12 = (int *)(local_548 + -4);
            iVar5 = *piVar12;
            *piVar12 = *piVar12 + -1;
            UNLOCK();
            if (iVar5 == 1 || iVar5 + -1 < 0) {
              (**(code **)(**(int **)(local_548 + -0x10) + 4))();
            }
            LOCK();
            piVar12 = (int *)(local_55c + -4);
            iVar5 = *piVar12;
            *piVar12 = *piVar12 + -1;
            UNLOCK();
            if (iVar5 == 1 || iVar5 + -1 < 0) {
              (**(code **)(**(int **)(local_55c + -0x10) + 4))();
            }
          }
          FUN_00444db0((int)local_90);
        }
        if ((*(int *)(param_1 + 0x718) != 0) &&
           (uVar7 = FUN_00444230(local_90,L"Lightitems"), (char)uVar7 != '\0')) {
          pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"light_mode");
          if (7 < *(uint *)(pwVar10 + 10)) {
            pwVar10 = *(wchar_t **)pwVar10;
          }
          iVar11 = _wtoi(pwVar10);
          FUN_00409e30(local_30);
          iVar5 = *(int *)(param_1 + 0x6f0);
          puVar9 = FUN_00401170();
          FUN_00407830(puVar9,iVar5,iVar11);
          FUN_00444d70((int)local_90);
          while (uVar7 = FUN_00444230(local_90,L"item"), (char)uVar7 != '\0') {
            pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"light_mode");
            if (7 < *(uint *)(pwVar10 + 10)) {
              pwVar10 = *(wchar_t **)pwVar10;
            }
            iVar5 = _wtoi(pwVar10);
            if (7 < local_1c) {
              FUN_0040a470(local_30[0],local_1c + 1);
            }
            FUN_00407630(local_578);
            puVar15 = local_578;
            local_8 = CONCAT31(local_8._1_3_,8);
            iVar11 = *(int *)(param_1 + 0x6f0);
            iVar14 = iVar5;
            puVar9 = FUN_00401170();
            cVar3 = FUN_004079f0(puVar9,iVar11,iVar14,puVar15);
            if (cVar3 != '\0') {
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"brightness");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_568 = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"speed");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_564 = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"direction");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_560 = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"colorful");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_55c = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"colorindex");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_558 = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              pwVar10 = (wchar_t *)FUN_0040e250(local_90,local_30,L"color_value");
              if (7 < *(uint *)(pwVar10 + 10)) {
                pwVar10 = *(wchar_t **)pwVar10;
              }
              local_554 = _wtoi(pwVar10);
              FUN_00409e30(local_30);
              puVar15 = local_578;
              iVar11 = *(int *)(param_1 + 0x6f0);
              puVar9 = FUN_00401170();
              FUN_00407700(puVar9,iVar11,iVar5,(int)puVar15);
            }
            local_8 = CONCAT31(local_8._1_3_,5);
            LOCK();
            piVar12 = (int *)(local_570 + -4);
            iVar5 = *piVar12;
            *piVar12 = *piVar12 + -1;
            UNLOCK();
            if (iVar5 == 1 || iVar5 + -1 < 0) {
              (**(code **)(**(int **)(local_570 + -0x10) + 4))();
            }
          }
          FUN_00444db0((int)local_90);
        }
        FUN_004055b0(&local_53c);
        local_8._0_1_ = 9;
        uVar7 = FUN_00444230(local_90,L"Mouse_DPI");
        iVar5 = local_53c;
        if ((char)uVar7 != '\0') {
          psVar8 = (short *)FUN_0040e250(local_90,local_30,L"dpi_flag");
          local_8._0_1_ = 10;
          if (7 < *(uint *)(psVar8 + 10)) {
            psVar8 = *(short **)psVar8;
          }
          FUN_004053e0(&local_53c,psVar8);
          local_8._0_1_ = 9;
          FUN_00409e30(local_30);
          local_534 = &stack0xfffffa74;
          local_538 = &stack0xfffffa74;
          piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
          piVar12 = piVar12 + 4;
          local_538 = &stack0xfffffa70;
          local_8._0_1_ = 0xb;
          iVar11 = extraout_ECX;
          FUN_004054f0(&stack0xfffffa70,L"dpi_flag");
          local_8._0_1_ = 0xc;
          iVar5 = *(int *)(param_1 + 0x6f0);
          puVar9 = FUN_00401170();
          local_8._0_1_ = 9;
          FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
          psVar8 = (short *)FUN_0040e250(local_90,local_30,L"dpi_index");
          local_8._0_1_ = 0xd;
          if (7 < *(uint *)(psVar8 + 10)) {
            psVar8 = *(short **)psVar8;
          }
          FUN_004053e0(&local_53c,psVar8);
          local_8._0_1_ = 9;
          FUN_00409e30(local_30);
          local_538 = &stack0xfffffa74;
          local_534 = &stack0xfffffa74;
          piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
          piVar12 = piVar12 + 4;
          local_534 = &stack0xfffffa70;
          local_8._0_1_ = 0xe;
          iVar11 = extraout_ECX_00;
          FUN_004054f0(&stack0xfffffa70,L"dpi_index");
          local_8._0_1_ = 0xf;
          iVar5 = *(int *)(param_1 + 0x6f0);
          puVar9 = FUN_00401170();
          local_8._0_1_ = 9;
          FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
          psVar8 = (short *)FUN_0040e250(local_90,local_30,L"dpi_count");
          local_8._0_1_ = 0x10;
          if (7 < *(uint *)(psVar8 + 10)) {
            psVar8 = *(short **)psVar8;
          }
          FUN_004053e0(&local_53c,psVar8);
          local_8._0_1_ = 9;
          FUN_00409e30(local_30);
          iVar5 = local_53c;
          local_538 = &stack0xfffffa74;
          local_534 = &stack0xfffffa74;
          piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
          piVar12 = piVar12 + 4;
          local_534 = &stack0xfffffa70;
          local_8._0_1_ = 0x11;
          iVar14 = extraout_ECX_01;
          FUN_004054f0(&stack0xfffffa70,L"dpi_count");
          local_8._0_1_ = 0x12;
          iVar11 = *(int *)(param_1 + 0x6f0);
          puVar9 = FUN_00401170();
          local_8._0_1_ = 9;
          FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          FUN_00444d70((int)local_90);
          uVar7 = FUN_00444230(local_90,L"DPI1");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x13;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x14;
            iVar11 = extraout_ECX_02;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group0_value");
            local_8._0_1_ = 0x15;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x16;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x17;
            iVar14 = extraout_ECX_03;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group0_rgb");
            local_8._0_1_ = 0x18;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"DPI2");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x19;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x1a;
            iVar11 = extraout_ECX_04;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group1_value");
            local_8._0_1_ = 0x1b;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x1c;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x1d;
            iVar14 = extraout_ECX_05;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group1_rgb");
            local_8._0_1_ = 0x1e;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"DPI3");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x1f;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x20;
            iVar11 = extraout_ECX_06;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group2_value");
            local_8._0_1_ = 0x21;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x22;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x23;
            iVar14 = extraout_ECX_07;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group2_rgb");
            local_8._0_1_ = 0x24;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"DPI4");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x25;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x26;
            iVar11 = extraout_ECX_08;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group3_value");
            local_8._0_1_ = 0x27;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x28;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x29;
            iVar14 = extraout_ECX_09;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group3_rgb");
            local_8._0_1_ = 0x2a;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"DPI5");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x2b;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x2c;
            iVar11 = extraout_ECX_10;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group4_value");
            local_8._0_1_ = 0x2d;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x2e;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x2f;
            iVar14 = extraout_ECX_11;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group4_rgb");
            local_8._0_1_ = 0x30;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"DPI6");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x31;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x32;
            iVar11 = extraout_ECX_12;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group5_value");
            local_8._0_1_ = 0x33;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"color");
            local_8._0_1_ = 0x34;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x35;
            iVar14 = extraout_ECX_13;
            FUN_004054f0(&stack0xfffffa70,L"dpi_group5_rgb");
            local_8._0_1_ = 0x36;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          FUN_00444db0((int)local_90);
        }
        uVar7 = FUN_00444230(local_90,L"Mouse");
        if ((char)uVar7 != '\0') {
          FUN_00444d70((int)local_90);
          uVar7 = FUN_00444230(local_90,L"button_respondtime");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x37;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x38;
            iVar14 = extraout_ECX_14;
            FUN_004054f0(&stack0xfffffa70,L"button_respondtime");
            local_8._0_1_ = 0x39;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"report_rate");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x3a;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x3b;
            iVar14 = extraout_ECX_15;
            FUN_004054f0(&stack0xfffffa70,L"report_rate");
            local_8._0_1_ = 0x3c;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"sensor_flag");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x3d;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x3e;
            iVar14 = extraout_ECX_16;
            FUN_004054f0(&stack0xfffffa70,L"sensor_flag");
            local_8._0_1_ = 0x3f;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"liftoff_height");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x40;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x41;
            iVar14 = extraout_ECX_17;
            FUN_004054f0(&stack0xfffffa70,L"liftoff_height");
            local_8._0_1_ = 0x42;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"scroll_flag");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x43;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x44;
            iVar14 = extraout_ECX_18;
            FUN_004054f0(&stack0xfffffa70,L"scroll_flag");
            local_8._0_1_ = 0x45;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"e-sports_flag");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x46;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            iVar5 = local_53c;
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x47;
            iVar14 = extraout_ECX_19;
            FUN_004054f0(&stack0xfffffa70,L"e-sports_flag");
            local_8._0_1_ = 0x48;
            iVar11 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar11,iVar14,(int)piVar12);
          }
          uVar7 = FUN_00444230(local_90,L"leftbtn_lock");
          if ((char)uVar7 != '\0') {
            psVar8 = (short *)FUN_0040e250(local_90,local_30,L"value");
            local_8._0_1_ = 0x49;
            if (7 < *(uint *)(psVar8 + 10)) {
              psVar8 = *(short **)psVar8;
            }
            FUN_004053e0(&local_53c,psVar8);
            local_8._0_1_ = 9;
            FUN_00409e30(local_30);
            local_538 = &stack0xfffffa74;
            local_534 = &stack0xfffffa74;
            piVar12 = FUN_00405df0((int *)(local_53c + -0x10));
            piVar12 = piVar12 + 4;
            local_534 = &stack0xfffffa70;
            local_8._0_1_ = 0x4a;
            iVar11 = extraout_ECX_20;
            FUN_004054f0(&stack0xfffffa70,L"leftbtn_lock");
            local_8._0_1_ = 0x4b;
            iVar5 = *(int *)(param_1 + 0x6f0);
            puVar9 = FUN_00401170();
            local_8._0_1_ = 9;
            FUN_00401860(puVar9,iVar5,iVar11,(int)piVar12);
            iVar5 = local_53c;
          }
        }
        local_534 = (undefined1 *)0x11;
        if (*(int *)(param_1 + 0x6e8) < 0xc9) {
          local_534 = (undefined1 *)0x5;
        }
        FUN_0040c780(param_1 + 0x688,&local_534);
        local_8._0_1_ = 5;
        LOCK();
        piVar12 = (int *)(iVar5 + -4);
        iVar11 = *piVar12;
        *piVar12 = *piVar12 + -1;
        UNLOCK();
        if (iVar11 == 1 || iVar11 + -1 < 0) {
          (**(code **)(**(int **)(iVar5 + -0x10) + 4))();
        }
        local_8._0_1_ = 2;
        LOCK();
        piVar12 = (int *)(local_544 + -4);
        iVar5 = *piVar12;
        *piVar12 = *piVar12 + -1;
        UNLOCK();
        if (iVar5 == 1 || iVar5 + -1 < 0) {
          (**(code **)(**(int **)(local_544 + -0x10) + 4))();
        }
      }
      FUN_00443c50(local_90);
    }
    local_8 = (uint)local_8._1_3_ << 8;
    LOCK();
    pWVar1 = local_540 + -2;
    iVar5 = *(int *)pWVar1;
    *(int *)pWVar1 = *(int *)pWVar1 + -1;
    UNLOCK();
    if (iVar5 == 1 || iVar5 + -1 < 0) {
      (**(code **)(**(int **)(local_540 + -8) + 4))();
    }
  }
  if (local_51c != (int *)0x0) {
    FUN_00447dcb(local_51c);
  }
  ExceptionList = local_10;
  __security_check_cookie(local_18 ^ (uint)&stack0xfffffffc);
  return;
}

