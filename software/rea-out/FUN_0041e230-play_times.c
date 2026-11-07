
void __fastcall FUN_0041e230(MWindow *param_1)

{
  void *pvVar1;
  wchar_t *pwVar2;
  LPITEMIDLIST pidl;
  wchar_t *pwVar3;
  int *piVar4;
  int iVar5;
  undefined *puVar6;
  wchar_t *pwVar7;
  undefined4 *puVar8;
  void *pvVar9;
  bool bVar10;
  void **ppvVar11;
  _browseinfoW local_2d4;
  undefined4 local_2b4;
  int local_2b0;
  void *local_29c;
  void *local_298;
  int local_294;
  wchar_t *local_290;
  int local_28c;
  wchar_t *local_288;
  wchar_t *local_284;
  wchar_t *local_280;
  undefined4 local_27c [6];
  int local_264 [6];
  wchar_t *local_24c;
  wchar_t *local_248;
  wchar_t *local_244;
  uint local_238;
  undefined4 local_234;
  undefined4 local_230;
  byte local_22c [12];
  int *local_220;
  WCHAR local_21c [260];
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0053517d;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_284 = (wchar_t *)YJXUI::MacroList::GetCurSel(*(MacroList **)(param_1 + 0x4a0));
  if (-1 < (int)local_284) {
    local_2d4.hwndOwner = (HWND)0x0;
    local_2d4.pidlRoot = (LPCITEMIDLIST)0x0;
    local_2d4.pszDisplayName = (LPWSTR)0x0;
    local_2d4.lpszTitle = (LPCWSTR)0x0;
    local_2d4.ulFlags = 0;
    local_2d4.lpfn = (BFFCALLBACK)0x0;
    local_2d4.lParam = 0;
    local_2d4.iImage = 0;
    local_2d4.hwndOwner = YJXUI::MWindow::GetSafeHwnd(param_1);
    local_2d4.lpszTitle = L"Macro";
    local_2d4.ulFlags = 0x40;
    memset(local_21c,0,0x208);
    pidl = SHBrowseForFolderW(&local_2d4);
    SHGetPathFromIDListW(pidl,local_21c);
    FUN_004054f0(&local_28c,local_21c);
    pwVar3 = local_284;
    local_8 = 0;
    if (*(int *)(local_28c + -0xc) != 0) {
      YJXUI::MacroList::GetItemText(*(MacroList **)(param_1 + 0x4a0),(int)&local_288);
      local_8._0_1_ = 1;
      pwVar3 = (wchar_t *)
               YJXUI::MacroList::GetItemData(*(MacroList **)(param_1 + 0x4a0),(int)pwVar3);
      local_284 = pwVar3;
      piVar4 = (int *)FUN_00406b10();
      if (piVar4 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
        FUN_00406bc0(0x80004005);
      }
      iVar5 = (**(code **)(*piVar4 + 0xc))();
      local_280 = (wchar_t *)(iVar5 + 0x10);
      local_8._0_1_ = 2;
      FUN_0040e170(local_27c);
      local_8._0_1_ = 3;
      FUN_00443d30(local_27c,(int *)L"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\r\n");
      FUN_00446570(local_27c,(int *)L"macro",(wchar_t *)0x0,0);
      if ((local_248 != (wchar_t *)0x0) && (local_238 == 1)) {
        local_24c = local_248;
        bVar10 = local_244 != (wchar_t *)0x0;
        local_248 = local_244;
        local_244 = (wchar_t *)0x0;
        local_238 = (uint)bVar10;
        local_234 = 0;
        local_230 = 0;
      }
      FUN_00446570(local_27c,(int *)L"macroinfo",(wchar_t *)0x0,0);
      FUN_00407e20(&local_2b4);
      puVar8 = &local_2b4;
      local_8 = CONCAT31(local_8._1_3_,4);
      puVar6 = FUN_00401170();
      FUN_004083f0(puVar6,(int)pwVar3,puVar8);
      if ((int)(*(uint *)(local_288 + -4) | 1U - *(int *)(local_288 + -2)) < 0) {
        FUN_00405e50(&local_288,0);
      }
      FUN_00445a00(local_27c,(uint)local_248,L"macro_name",local_288,0);
      FUN_00406540(&local_280,0x54a358);
      if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
        FUN_00405e50(&local_280,0);
      }
      FUN_00445a00(local_27c,(uint)local_248,L"macro_type",local_280,0);
      FUN_00406540(&local_280,0x54a358);
      if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
        FUN_00405e50(&local_280,0);
      }
      FUN_00445a00(local_27c,(uint)local_248,L"play_times",local_280,0);
      FUN_00406540(&local_280,0x54a358);
      if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
        FUN_00405e50(&local_280,0);
      }
      FUN_00445a00(local_27c,(uint)local_248,L"delay_type",local_280,0);
      FUN_00406540(&local_280,0x54a358);
      if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
        FUN_00405e50(&local_280,0);
      }
      pwVar3 = local_280;
      FUN_00445a00(local_27c,(uint)local_248,L"delay_time",local_280,0);
      FUN_00446570(local_27c,(int *)L"macroitems",(wchar_t *)0x0,0);
      if ((local_248 != (wchar_t *)0x0) && (local_238 == 1)) {
        local_24c = local_248;
        bVar10 = local_244 != (wchar_t *)0x0;
        local_248 = local_244;
        local_244 = (wchar_t *)0x0;
        local_238 = (uint)bVar10;
        local_234 = 0;
        local_230 = 0;
      }
      local_29c = (void *)0x0;
      local_298 = (void *)0x0;
      local_294 = 0;
      ppvVar11 = &local_29c;
      local_8 = CONCAT31(local_8._1_3_,5);
      pwVar7 = local_284;
      puVar6 = FUN_00401170();
      iVar5 = FUN_00408c90(puVar6,(undefined4 *)pwVar7,(int *)ppvVar11);
      pvVar9 = local_298;
      if (0 < iVar5) {
        pwVar7 = (wchar_t *)((int)local_298 - (int)local_29c >> 2);
        local_284 = (wchar_t *)0x0;
        pvVar9 = local_29c;
        local_290 = pwVar7;
        if (pwVar7 != (wchar_t *)0x0) {
          pvVar9 = local_29c;
          if (pwVar7 == (wchar_t *)0x0) {
                    /* WARNING: Subroutine does not return */
            std::_Xout_of_range("invalid vector<T> subscript");
          }
          do {
            pvVar1 = *(void **)((int)pvVar9 + (int)local_284 * 4);
            if (pvVar1 != (void *)0x0) {
              FUN_00446570(local_27c,(int *)L"item",(wchar_t *)0x0,0);
              if ((int)(*(uint *)(*(int *)((int)pvVar1 + 0x18) + -8) |
                       1U - *(int *)(*(int *)((int)pvVar1 + 0x18) + -4)) < 0) {
                FUN_00405e50((void *)((int)pvVar1 + 0x18),0);
              }
              FUN_00445a00(local_27c,(uint)local_248,L"desc",*(wchar_t **)((int)pvVar1 + 0x18),0);
              FUN_00406540(&local_280,0x54a358);
              if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
                FUN_00405e50(&local_280,0);
              }
              FUN_00445a00(local_27c,(uint)local_248,L"index",local_280,0);
              FUN_00406540(&local_280,0x54a358);
              if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
                FUN_00405e50(&local_280,0);
              }
              FUN_00445a00(local_27c,(uint)local_248,L"type",local_280,0);
              FUN_00406540(&local_280,0x54a358);
              if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
                FUN_00405e50(&local_280,0);
              }
              FUN_00445a00(local_27c,(uint)local_248,L"value",local_280,0);
              FUN_00406540(&local_280,0x54a358);
              if ((int)(*(uint *)(local_280 + -4) | 1U - *(int *)(local_280 + -2)) < 0) {
                FUN_00405e50(&local_280,0);
              }
              pwVar3 = local_280;
              FUN_00445a00(local_27c,(uint)local_248,L"timestamp",local_280,0);
              puVar8 = (undefined4 *)(*(int *)((int)pvVar1 + 0x18) + -0x10);
              LOCK();
              piVar4 = (int *)(*(int *)((int)pvVar1 + 0x18) + -4);
              iVar5 = *piVar4;
              *piVar4 = *piVar4 + -1;
              UNLOCK();
              if (iVar5 == 1 || iVar5 + -1 < 0) {
                (**(code **)(*(int *)*puVar8 + 4))(puVar8);
              }
              FUN_004484a6(pvVar1);
              pwVar7 = local_290;
              pvVar9 = local_29c;
            }
            local_284 = (wchar_t *)((int)local_284 + 1);
          } while (local_284 < pwVar7);
        }
      }
      local_298 = pvVar9;
      pwVar7 = local_248;
      local_284 = local_24c;
      pwVar2 = local_24c;
      if (local_24c != (wchar_t *)0x0) {
        local_290 = *(wchar_t **)
                     (*(int *)(*local_220 + ((int)local_24c >> 0x10) * 4) + 0x10 +
                     ((uint)local_24c & 0xffff) * 0x20);
        local_238 = (uint)(local_24c != (wchar_t *)0x0);
        local_248 = local_24c;
        local_244 = pwVar7;
        local_234 = 0;
        local_230 = 0;
        pwVar2 = local_290;
        if (local_290 != (wchar_t *)0x0) {
          local_244 = local_24c;
          local_234 = 0;
          local_238 = (uint)(local_290 != (wchar_t *)0x0);
          local_230 = 0;
          pwVar2 = *(wchar_t **)
                    (*(int *)(*local_220 + ((int)local_290 >> 0x10) * 4) + 0x10 +
                    ((uint)local_290 & 0xffff) * 0x20);
          local_248 = local_290;
        }
      }
      local_24c = pwVar2;
      piVar4 = (int *)FUN_00406b10();
      if (piVar4 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
        FUN_00406bc0(0x80004005);
      }
      iVar5 = (**(code **)(*piVar4 + 0xc))();
      local_284 = (wchar_t *)(iVar5 + 0x10);
      local_8 = CONCAT31(local_8._1_3_,6);
      GetTickCount();
      FUN_00406540(&local_284,0x54ce8c);
      if ((int)(*(uint *)(local_284 + -4) | 1U - *(int *)(local_284 + -2)) < 0) {
        FUN_00405e50(&local_284,0);
      }
      pwVar7 = local_284;
      if ((local_22c[0] & 0x30) == 0) {
        FUN_004440a0(local_27c,local_264,local_284,(uint *)local_22c);
      }
      pwVar2 = pwVar7 + -8;
      local_8 = CONCAT31(local_8._1_3_,5);
      LOCK();
      pwVar7 = pwVar7 + -2;
      iVar5 = *(int *)pwVar7;
      *(int *)pwVar7 = *(int *)pwVar7 + -1;
      UNLOCK();
      if (iVar5 == 1 || iVar5 + -1 < 0) {
        (**(code **)(**(int **)pwVar2 + 4))(pwVar2);
      }
      if (local_29c != (void *)0x0) {
        FUN_00406040(local_29c,local_294 - (int)local_29c >> 2);
      }
      local_8._0_1_ = 3;
      LOCK();
      piVar4 = (int *)(local_2b0 + -4);
      iVar5 = *piVar4;
      *piVar4 = *piVar4 + -1;
      UNLOCK();
      if (iVar5 == 1 || iVar5 + -1 < 0) {
        (**(code **)(**(int **)(local_2b0 + -0x10) + 4))((undefined4 *)(local_2b0 + -0x10));
      }
      FUN_00443c50(local_27c);
      local_8._0_1_ = 1;
      LOCK();
      pwVar7 = pwVar3 + -2;
      iVar5 = *(int *)pwVar7;
      *(int *)pwVar7 = *(int *)pwVar7 + -1;
      UNLOCK();
      if (iVar5 == 1 || iVar5 + -1 < 0) {
        (**(code **)(**(int **)(pwVar3 + -8) + 4))(pwVar3 + -8);
      }
      local_8 = (uint)local_8._1_3_ << 8;
      LOCK();
      pwVar3 = local_288 + -2;
      iVar5 = *(int *)pwVar3;
      *(int *)pwVar3 = *(int *)pwVar3 + -1;
      UNLOCK();
      if (iVar5 == 1 || iVar5 + -1 < 0) {
        (**(code **)(**(int **)(local_288 + -8) + 4))(local_288 + -8);
      }
    }
    local_8 = 0xffffffff;
    LOCK();
    piVar4 = (int *)(local_28c + -4);
    iVar5 = *piVar4;
    *piVar4 = *piVar4 + -1;
    UNLOCK();
    if (iVar5 == 1 || iVar5 + -1 < 0) {
      (**(code **)(**(int **)(local_28c + -0x10) + 4))((undefined4 *)(local_28c + -0x10));
    }
  }
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

