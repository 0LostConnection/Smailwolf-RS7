
/* WARNING: Function: __alloca_probe replaced with injection: alloca_probe */

void FUN_0042ac40(void)

{
  int *piVar1;
  byte *pbVar2;
  undefined1 uVar3;
  char cVar4;
  void *pvVar5;
  int iVar6;
  undefined4 uVar7;
  byte bVar8;
  uint uVar9;
  uint uVar10;
  int iVar11;
  wchar_t *pwVar12;
  void *pvVar13;
  undefined4 *puVar14;
  uint uVar15;
  uint uVar16;
  uint uVar17;
  void *local_1114;
  void *local_1110;
  int local_110c;
  int local_1108;
  int local_1104;
  void *local_1100;
  void *local_10fc;
  int local_10f8;
  uint local_10f4;
  uint local_10f0;
  undefined4 *local_10ec;
  uint local_10e8;
  uint local_10e4;
  uint local_10e0;
  undefined4 local_10dc;
  undefined4 local_10d8;
  byte abStack_109c [6];
  undefined2 uStack_1096;
  char local_58;
  undefined4 local_57;
  undefined4 local_53;
  undefined4 local_4f;
  undefined4 uStack_4b;
  undefined4 uStack_47;
  undefined4 uStack_43;
  undefined4 local_3f;
  undefined4 uStack_3b;
  undefined4 uStack_37;
  undefined4 uStack_33;
  undefined4 local_2f;
  undefined4 uStack_2b;
  undefined4 uStack_27;
  undefined4 uStack_23;
  undefined8 local_1f;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_00536356;
  local_10 = ExceptionList;
  local_14 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  memset(&local_10d8,0,0x1080);
  local_1114 = (void *)0x0;
  uVar15 = 0x40;
  local_1110 = (void *)0x0;
  local_110c = 0;
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  local_1108 = *(int *)ThreadLocalStoragePointer;
  if ((*(int *)(local_1108 + 4) < DAT_0056ef90) && (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)
     ) {
    local_8._0_1_ = 1;
    FUN_00401290();
    _atexit(thunk_FUN_004013b0);
    local_8._0_1_ = 0;
    FUN_00448621(&DAT_0056ef90);
  }
  uVar9 = FUN_00408690(&DAT_0056ef20,(int *)&local_1114);
  if (0 < (int)uVar9) {
    local_10f4 = 0;
    if (0 < (int)uVar9) {
      uVar10 = (int)local_1110 - (int)local_1114 >> 2;
      pvVar13 = local_1114;
      uVar16 = uVar15;
      local_10f0 = uVar10;
      local_10e0 = uVar9;
      do {
        uVar17 = local_10f4;
        if (uVar10 <= local_10f4) {
LAB_0042b45f:
                    /* WARNING: Subroutine does not return */
          std::_Xout_of_range("invalid vector<T> subscript");
        }
        puVar14 = *(undefined4 **)((int)pvVar13 + local_10f4 * 4);
        uVar15 = uVar16;
        local_10ec = puVar14;
        if (puVar14 != (undefined4 *)0x0) {
          *(char *)((int)&local_10d8 + local_10f4 * 2) = (char)uVar16;
          *(char *)((int)&local_10d8 + local_10f4 * 2 + 1) = (char)(uVar16 >> 8);
          local_1100 = (void *)0x0;
          local_10fc = (void *)0x0;
          local_10f8 = 0;
          local_8._0_1_ = 2;
          if ((*(int *)(local_1108 + 4) < DAT_0056ef90) &&
             (FUN_00448660(&DAT_0056ef90), DAT_0056ef90 == -1)) {
            local_8._0_1_ = 3;
            FUN_00401290();
            _atexit(thunk_FUN_004013b0);
            local_8._0_1_ = 2;
            FUN_00448621(&DAT_0056ef90);
          }
          iVar11 = FUN_00408c90(&DAT_0056ef20,(undefined4 *)*puVar14,(int *)&local_1100);
          local_1104 = iVar11;
          if (iVar11 < 1) {
            if (0x107f < uVar16) {
LAB_0042b46a:
                    /* WARNING: Subroutine does not return */
              ___report_rangecheckfailure();
            }
            *(undefined1 *)((int)&local_10d8 + uVar16) = 0;
            if (0x107f < uVar16 + 1) goto LAB_0042b46a;
            *(undefined1 *)((int)&local_10d8 + uVar16 + 1) = 0;
            pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
            *pbVar2 = *pbVar2 | 0x80;
            if (0x107f < uVar16 + 3) goto LAB_0042b46a;
            uVar15 = uVar16 + 4;
            *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = 0;
          }
          else {
            local_10e4 = 0;
            uVar15 = 1;
            if (0 < iVar11) {
              uVar9 = (int)local_10fc - (int)local_1100 >> 2;
              pvVar13 = local_1100;
              local_10e8 = uVar9;
              do {
                if (uVar9 <= local_10e4) goto LAB_0042b45f;
                pvVar5 = *(void **)((int)pvVar13 + local_10e4 * 4);
                if (pvVar5 != (void *)0x0) {
                  iVar6 = *(int *)((int)pvVar5 + 8);
                  if (iVar6 == 1) {
                    local_10dc = uVar15 + *(int *)((int)pvVar5 + 0x10);
                    if (local_10e4 == iVar11 - 1U) {
                      *(byte *)((int)&local_10dc + uVar16) =
                           *(byte *)((int)&local_10dc + uVar16) | (byte)local_10dc;
                      pbVar2 = (byte *)((int)&local_10dc + uVar16 + 1);
                      *pbVar2 = *pbVar2 | (byte)(local_10dc >> 8);
                      pbVar2 = (byte *)((int)&local_10dc + uVar16 + 2);
                      *pbVar2 = *pbVar2 | 0x80;
                    }
                    puVar14 = (undefined4 *)(*(int *)((int)pvVar5 + 0x18) + -0x10);
                    LOCK();
                    piVar1 = (int *)(*(int *)((int)pvVar5 + 0x18) + -4);
                    iVar6 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar6 == 1 || iVar6 + -1 < 0) {
                      (**(code **)(*(int *)*puVar14 + 4))(puVar14);
                    }
                    FUN_004484a6(pvVar5);
                    pvVar13 = local_1100;
                    uVar15 = local_10dc;
                    uVar9 = local_10e8;
                  }
                  else {
                    if (0x40 < (int)uVar16) {
                      if ((int)uVar15 < 1) {
                        uVar15 = 10;
                      }
                      *(byte *)((int)&local_10dc + uVar16) =
                           *(byte *)((int)&local_10dc + uVar16) | (byte)uVar15;
                      pbVar2 = (byte *)((int)&local_10dc + uVar16 + 1);
                      *pbVar2 = *pbVar2 | (byte)(uVar15 >> 8);
                    }
                    if (iVar6 == 2) {
                      pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                      *pbVar2 = *pbVar2 | 0x40;
                      local_10dc = *(uint *)((int)pvVar5 + 0x10);
                      bVar8 = *(byte *)((int)&local_10d8 + uVar16 + 2);
                      if (((int)local_10dc < 0xe0) || (0xe7 < (int)local_10dc)) {
                        bVar8 = bVar8 | 2;
                      }
                      else {
                        bVar8 = bVar8 | 1;
                      }
                      *(byte *)((int)&local_10d8 + uVar16 + 2) = bVar8;
                      uVar15 = FUN_0043e570(&local_10dc);
                      *(char *)((int)&local_10d8 + uVar16 + 3) = (char)uVar15;
                    }
                    else if (iVar6 == 3) {
                      local_10dc = *(uint *)((int)pvVar5 + 0x10);
                      if (((int)local_10dc < 0xe0) || (0xe7 < (int)local_10dc)) {
                        pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                        *pbVar2 = *pbVar2 | 2;
                      }
                      else {
                        pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                        *pbVar2 = *pbVar2 | 1;
                      }
                      uVar15 = FUN_0043e570(&local_10dc);
                      *(char *)((int)&local_10d8 + uVar16 + 3) = (char)uVar15;
                    }
                    else if (iVar6 == 4) {
                      uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                      pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                      *pbVar2 = *pbVar2 | 0x43;
                      *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                      if ((-1 < *(int *)(*(wchar_t **)((int)pvVar5 + 0x18) + -6)) &&
                         (pwVar12 = wcsstr(*(wchar_t **)((int)pvVar5 + 0x18),L"Scroll Up"),
                         pwVar12 != (wchar_t *)0x0)) {
                        iVar11 = (int)pwVar12 - *(int *)((int)pvVar5 + 0x18) >> 1;
LAB_0042afa2:
                        if (iVar11 != -1) {
                          *(undefined2 *)((int)&local_10d8 + uVar16 + 2) = 0x144;
                          goto LAB_0042b0e0;
                        }
                      }
                      iVar11 = FUN_0040a020((void *)((int)pvVar5 + 0x18),L"Scroll Down");
                      if (iVar11 != -1) {
                        *(undefined2 *)((int)&local_10d8 + uVar16 + 2) = 0xff44;
                      }
                    }
                    else {
                      if (iVar6 == 5) {
                        uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                        pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                        *pbVar2 = *pbVar2 | 3;
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                        iVar11 = FUN_0040a020((void *)((int)pvVar5 + 0x18),L"Scroll Up");
                        goto LAB_0042afa2;
                      }
                      if (iVar6 == 6) {
                        *(undefined2 *)((int)&local_10d8 + uVar16 + 2) = 0x144;
                      }
                      else if (iVar6 == 7) {
                        *(undefined2 *)((int)&local_10d8 + uVar16 + 2) = 0xff44;
                      }
                      else if (iVar6 == 8) {
                        uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 2) = 0x46;
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                      }
                      else if (iVar6 == 9) {
                        uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 2) = 0x46;
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                      }
                      else if (iVar6 == 10) {
                        uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 2) = 0x46;
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                      }
                      else if (iVar6 == 0xb) {
                        uVar3 = *(undefined1 *)((int)pvVar5 + 0x10);
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 2) = 0x46;
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 3) = uVar3;
                      }
                      else if (iVar6 == 0xc) {
                        bVar8 = *(byte *)((int)pvVar5 + 0x11);
                        cVar4 = *(char *)((int)pvVar5 + 0x10);
                        *(undefined1 *)((int)&local_10d8 + uVar16 + 2) = 0x46;
                        *(byte *)((int)&local_10d8 + uVar16 + 3) = bVar8 & 0xf | cVar4 << 4;
                        if (cVar4 < '\0') {
                          pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 1);
                          *pbVar2 = *pbVar2 | 0x40;
                        }
                        if ((bVar8 & 0x80) != 0) {
                          pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 1);
                          *pbVar2 = *pbVar2 | 0x80;
                        }
                      }
                    }
LAB_0042b0e0:
                    if (local_10e4 == local_1104 - 1U) {
                      pbVar2 = (byte *)((int)&local_10d8 + uVar16 + 2);
                      *pbVar2 = *pbVar2 | 0x80;
                    }
                    uVar16 = uVar16 + 4;
                    local_10dc = 0;
                    puVar14 = (undefined4 *)(*(int *)((int)pvVar5 + 0x18) + -0x10);
                    LOCK();
                    piVar1 = (int *)(*(int *)((int)pvVar5 + 0x18) + -4);
                    iVar11 = *piVar1;
                    *piVar1 = *piVar1 + -1;
                    UNLOCK();
                    if (iVar11 == 1 || iVar11 + -1 < 0) {
                      (**(code **)(*(int *)*puVar14 + 4))(puVar14);
                    }
                    FUN_004484a6(pvVar5);
                    pvVar13 = local_1100;
                    uVar15 = local_10dc;
                    uVar9 = local_10e8;
                    iVar11 = local_1104;
                  }
                }
                local_10e4 = local_10e4 + 1;
              } while ((int)local_10e4 < iVar11);
            }
            local_10fc = local_1100;
            uVar15 = uVar16;
            uVar17 = local_10f4;
          }
          pvVar5 = local_1100;
          puVar14 = (undefined4 *)(local_10ec[1] + -0x10);
          LOCK();
          piVar1 = (int *)(local_10ec[1] + -4);
          iVar11 = *piVar1;
          *piVar1 = *piVar1 + -1;
          UNLOCK();
          if (iVar11 == 1 || iVar11 + -1 < 0) {
            (**(code **)(*(int *)*puVar14 + 4))(puVar14);
          }
          FUN_004484a6(local_10ec);
          local_8._0_1_ = 0;
          uVar10 = local_10f0;
          pvVar13 = local_1114;
          uVar9 = local_10e0;
          if (pvVar5 != (void *)0x0) {
            FUN_00406040(pvVar5,local_10f8 - (int)pvVar5 >> 2);
            local_1100 = (void *)0x0;
            local_10fc = (void *)0x0;
            local_10f8 = 0;
            uVar10 = local_10f0;
            pvVar13 = local_1114;
            uVar9 = local_10e0;
          }
        }
        local_10f4 = uVar17 + 1;
        uVar16 = uVar15;
      } while ((int)local_10f4 < (int)uVar9);
    }
    local_1110 = local_1114;
  }
  local_10e0 = 0;
  local_10ec = (undefined4 *)((int)uVar15 / 0x38);
  local_10f0 = (int)uVar15 % 0x38;
  local_10e8 = (int)local_10ec + 1;
  if (local_10f0 == 0) {
    local_10e8 = (uint)local_10ec;
  }
  if (0 < (int)local_10e8) {
    local_10f4 = local_10e8 - 1;
    iVar11 = 0;
    puVar14 = &local_10d8;
    do {
      memset(&local_58,0,0x41);
      uVar7 = local_53;
      local_57 = CONCAT22(local_57._2_2_,0xd55);
      local_53._3_1_ = SUB41(uVar7,3);
      local_53._0_3_ = CONCAT12((char)((uint)iVar11 >> 8),CONCAT11((char)local_10e0 * '8',0x38));
      if ((local_10e0 == local_10f4) && (local_10f0 != 0)) {
        local_53 = CONCAT31(local_53._1_3_,(char)uVar15 + (char)local_10ec * -0x38);
      }
      local_4f = *puVar14;
      uStack_4b = puVar14[1];
      uStack_47 = puVar14[2];
      uStack_43 = puVar14[3];
      local_3f = puVar14[4];
      uStack_3b = puVar14[5];
      uStack_37 = puVar14[6];
      uStack_33 = puVar14[7];
      local_2f = puVar14[8];
      uStack_2b = puVar14[9];
      uStack_27 = puVar14[10];
      uStack_23 = puVar14[0xb];
      local_1f = *(undefined8 *)(puVar14 + 0xc);
      if ((*(int *)(local_1108 + 4) < DAT_0056ef18) &&
         (FUN_00448660(&DAT_0056ef18), DAT_0056ef18 == -1)) {
        local_8._0_1_ = 4;
        FUN_0043b7c0();
        _atexit(thunk_FUN_0043b8c0);
        local_8._0_1_ = 0;
        FUN_00448621(&DAT_0056ef18);
      }
      FUN_0043be10(&DAT_0056eef0,&local_58);
      puVar14 = puVar14 + 0xe;
      local_10e0 = local_10e0 + 1;
      iVar11 = iVar11 + 0x38;
    } while ((int)local_10e0 < (int)local_10e8);
  }
  memset(&local_58,0,0x41);
  local_57 = 0x22a51055;
  local_53 = 0;
  if ((*(int *)(local_1108 + 4) < DAT_0056ef18) && (FUN_00448660(&DAT_0056ef18), DAT_0056ef18 == -1)
     ) {
    local_8._0_1_ = 5;
    FUN_0043b7c0();
    _atexit(thunk_FUN_0043b8c0);
    local_8._0_1_ = 0;
    FUN_00448621(&DAT_0056ef18);
  }
  FUN_0043be10(&DAT_0056eef0,&local_58);
  if (local_1114 != (void *)0x0) {
    FUN_00406040(local_1114,local_110c - (int)local_1114 >> 2);
  }
  ExceptionList = local_10;
  local_1110 = (void *)0x42b45b;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

