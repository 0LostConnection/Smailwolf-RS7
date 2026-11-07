
void FUN_00411ce0(int param_1,int param_2,uint param_3,uint param_4,int param_5)

{
  uint *puVar1;
  uint uVar2;
  uint uVar3;
  undefined4 *puVar4;
  int *piVar5;
  int iVar6;
  undefined *puVar7;
  uint uVar8;
  bool bVar9;
  undefined4 local_4c;
  undefined4 local_48;
  undefined4 local_44;
  int local_40;
  int local_38;
  int local_34;
  uint local_30;
  uint local_2c;
  int local_24;
  int local_20;
  int local_1c;
  undefined4 local_18;
  int local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  uVar8 = param_4;
  uVar2 = param_3;
  iVar6 = param_2;
  local_8 = 0xffffffff;
  puStack_c = &LAB_00533cd8;
  local_10 = ExceptionList;
  uVar3 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  if (param_2 == 0xff) {
    bVar9 = param_3 == 0xff;
LAB_00411d33:
    if (bVar9) {
      return;
    }
  }
  else if (((param_2 == 0) && (param_3 == 0)) && (param_4 == 0)) {
    bVar9 = param_5 == 0;
    goto LAB_00411d33;
  }
  ExceptionList = &local_10;
  FUN_00406c90(&local_4c);
  local_8._0_1_ = 0;
  local_8._1_3_ = 0;
  if (iVar6 == 0) {
    local_34 = 0x18;
    goto LAB_004124bc;
  }
  if (iVar6 == 0x10) {
    if (uVar2 == 8) {
      if (uVar8 == 8) {
        local_34 = 0x1a;
LAB_00411d85:
        FUN_00406540(&local_24,0x54a358);
        local_30 = 4;
      }
      else if (uVar8 == 7) {
        local_34 = 0x1a;
LAB_00411db3:
        FUN_00406540(&local_24,0x54a358);
        local_30 = 5;
      }
      else {
        if (uVar8 != 0x46) goto LAB_00411ef6;
        local_34 = 0x1a;
        FUN_00406540(&local_24,0x54a358);
        local_30 = 10;
      }
    }
    else if (uVar2 == 0) {
      if (uVar8 != 0x3e) goto LAB_00411ef6;
      local_34 = 0x1a;
LAB_00411e1b:
      FUN_00406540(&local_24,0x54a358);
      local_30 = 8;
    }
    else if (uVar2 == 4) {
      if (uVar8 == 0x2b) {
        local_34 = 0x1a;
        FUN_00406540(&local_24,0x54a358);
        local_30 = 9;
      }
      else {
LAB_00411ef6:
        local_34 = 0x16;
        local_30 = uVar8;
        local_2c = uVar2;
        puVar4 = FUN_0043ec10(&param_5,uVar8);
        local_8._0_1_ = 1;
        FUN_00405aa0(&local_24,puVar4);
        local_8._0_1_ = 0;
        FUN_00405430(&param_5);
        if (local_2c != 0) {
          FUN_004054f0(&param_5,(short *)&PTR_0054b37c);
          local_8._0_1_ = 2;
          FUN_004054f0(&param_2,(short *)&PTR_0054b37c);
          local_8 = CONCAT31(local_8._1_3_,3);
          if ((local_2c & 2) != 0) {
            FUN_004053e0(&param_5,L"Shift");
          }
          if ((local_2c & 1) != 0) {
            if (*(int *)(param_5 + -0xc) == 0) {
              FUN_004053e0(&param_5,L"Ctrl");
            }
            else {
              FUN_0040a960(&param_5,0x54c938);
            }
          }
          if ((local_2c & 8) != 0) {
            if (*(int *)(param_5 + -0xc) == 0) {
              FUN_004053e0(&param_5,(short *)&DAT_0054c948);
            }
            else {
              FUN_0040a960(&param_5,0x54c950);
            }
          }
          if ((local_2c & 4) != 0) {
            if (*(int *)(param_5 + -0xc) == 0) {
              FUN_004053e0(&param_5,(short *)&DAT_0054c95c);
            }
            else {
              FUN_0040a960(&param_5,0x54c964);
            }
          }
          if (*(int *)(param_5 + -0xc) == 0) {
LAB_00412027:
            piVar5 = &local_24;
LAB_0041202a:
            FUN_00405aa0(&param_2,piVar5);
          }
          else {
            if (*(int *)(local_24 + -0xc) == 0) {
              if ((*(int *)(param_5 + -0xc) == 0) ||
                 (piVar5 = &param_5, *(int *)(local_24 + -0xc) != 0)) goto LAB_00412027;
              goto LAB_0041202a;
            }
            FUN_00406540(&param_2,0x54c970);
          }
          FUN_00405aa0(&local_24,&param_2);
          FUN_00405430(&param_2);
          local_8._0_1_ = 0;
          FUN_00405430(&param_5);
        }
      }
    }
    else {
      if (uVar2 != 1) goto LAB_00411ef6;
      if (uVar8 == 6) {
        local_34 = 0x1a;
        FUN_00406540(&local_24,0x54a358);
        local_30 = 0xb;
      }
      else if (uVar8 == 0x19) {
        local_34 = 0x1a;
        FUN_00406540(&local_24,0x54a358);
        local_30 = 0xc;
      }
      else {
        if (uVar8 != 0x1b) goto LAB_00411ef6;
        local_34 = 0x1a;
        FUN_00406540(&local_24,0x54a358);
        local_30 = 0xd;
      }
    }
LAB_00412588:
    if (local_34 == 0) goto LAB_004125d2;
  }
  else if (iVar6 == 0x20) {
    if (uVar2 == 1) {
      if (uVar8 == 2) {
        FUN_00406540(&local_24,0x54a358);
        local_34 = 4;
        local_30 = uVar2;
      }
      else {
        FUN_00406540(&local_24,0x54a358);
        local_34 = 1;
        local_30 = 1;
      }
    }
    else if (uVar2 == 2) {
      FUN_00406540(&local_24,0x54a358);
      local_34 = 3;
      local_30 = 1;
    }
    else if (uVar2 == 4) {
      FUN_00406540(&local_24,0x54a358);
      local_34 = 2;
      local_30 = 1;
    }
    else if (uVar2 == 8) {
      FUN_00406540(&local_24,0x54a358);
      local_34 = 6;
      local_30 = 1;
    }
    else {
      if (uVar2 != 0x10) goto LAB_00412588;
      FUN_00406540(&local_24,0x54a358);
      local_34 = 5;
      local_30 = 1;
    }
  }
  else {
    if (iVar6 != 0x21) {
      if (iVar6 == 0x30) {
        if (uVar2 == 0xb5) {
          local_34 = 0x19;
          goto LAB_00411db3;
        }
        if (uVar2 == 0xb6) {
          local_34 = 0x19;
          goto LAB_00411d85;
        }
        if (uVar2 == 0xb7) {
          local_34 = 0x19;
LAB_00412396:
          FUN_00406540(&local_24,0x54a358);
          local_30 = 3;
        }
        else if (uVar2 == 0xcd) {
          local_34 = 0x19;
LAB_0041235c:
          FUN_00406540(&local_24,0x54a358);
          local_30 = 2;
        }
        else {
          if (uVar2 == 0xe2) {
            local_34 = 0x19;
            goto LAB_00411e1b;
          }
          if (uVar2 == 0xe9) {
            local_34 = 0x19;
LAB_004123cd:
            FUN_00406540(&local_24,0x54a358);
            local_30 = 6;
          }
          else if (uVar2 == 0xea) {
            local_34 = 0x19;
LAB_0041240b:
            FUN_00406540(&local_24,0x54a358);
            local_30 = 7;
          }
          else if (uVar2 == 0x83) {
            if (param_5 == 1) {
              local_34 = 0x19;
              goto LAB_004124bc;
            }
          }
          else {
            if (uVar2 == 0x6f) {
              local_34 = 0x1a;
              goto LAB_004124bc;
            }
            if (uVar2 == 0x70) {
              local_34 = 0x1a;
              goto LAB_0041235c;
            }
            if (uVar2 == 0x92) {
              if (uVar8 == 1) {
                local_34 = 0x1a;
                goto LAB_00412396;
              }
            }
            else if (uVar2 == 0x23) {
              if (uVar8 == 1) {
                local_34 = 0x1a;
                goto LAB_004123cd;
              }
            }
            else if ((uVar2 == 0x8a) && (uVar8 == 1)) {
              local_34 = 0x1a;
              goto LAB_0041240b;
            }
          }
        }
      }
      else if (iVar6 == 0xf0) {
        if (uVar2 == 1) {
          if (uVar8 == 1) {
            local_34 = 0xf;
          }
          else if (uVar8 == 2) {
            local_34 = 0x10;
          }
          else {
            if (uVar8 != 3) goto LAB_00412588;
            local_34 = 0x11;
          }
        }
        else {
          if (uVar2 != 2) goto LAB_00412588;
          if (uVar8 == 1) {
            local_34 = 0x13;
          }
          else if (uVar8 == 2) {
            local_34 = 0x14;
          }
          else {
            if (uVar8 != 3) goto LAB_00412588;
            local_34 = 0x15;
          }
        }
LAB_004124bc:
        FUN_00406540(&local_24,0x54a358);
        local_30 = 1;
      }
      else if (iVar6 == 0x70) {
        local_34 = 0x17;
        local_20 = 0;
        local_1c = 0;
        local_18 = 0;
        piVar5 = &local_20;
        local_8 = 4;
        puVar7 = FUN_00401170();
        iVar6 = FUN_00408690(puVar7,piVar5);
        uVar8 = 0;
        if (0 < iVar6) {
          do {
            if ((uint)(local_1c - local_20 >> 2) <= uVar8) {
                    /* WARNING: Subroutine does not return */
              std::_Xout_of_range("invalid vector<T> subscript");
            }
            puVar1 = *(uint **)(local_20 + uVar8 * 4);
            if ((puVar1 != (uint *)0x0) && (uVar2 == uVar8)) {
              local_30 = *puVar1;
              FUN_00405aa0(&local_24,puVar1 + 1);
              local_8._0_1_ = 0;
              FUN_0040fcc0(&local_20);
              goto LAB_00412588;
            }
            uVar8 = uVar8 + 1;
          } while ((int)uVar8 < iVar6);
        }
        local_8._0_1_ = 0;
        FUN_0040fcc0(&local_20);
      }
      else if (iVar6 == 0x50) {
        local_34 = 0x1b;
        local_30 = uVar2;
        FUN_004053e0(&local_24,(short *)&DAT_0054c980);
      }
      goto LAB_00412588;
    }
    if (uVar2 == 0x38) {
      if (uVar8 == 1) {
        FUN_00406540(&local_24,0x54a358);
        local_34 = 7;
        local_30 = uVar8;
      }
      else {
        if (uVar8 != 0xff) goto LAB_00412588;
        FUN_00406540(&local_24,0x54a358);
        local_34 = 8;
        local_30 = 1;
      }
    }
    else if (uVar2 == 0x55) {
      FUN_00406540(&local_24,0x54a358);
      local_34 = 9;
      local_30 = 1;
    }
    else if (uVar2 == 0xaa) {
      FUN_00406540(&local_24,0x54a358);
      local_34 = 10;
      local_30 = 1;
    }
    else {
      if (uVar2 != 0x61) goto LAB_00412588;
      FUN_00406540(&local_24,0x54a358);
      local_34 = 0xb;
      local_30 = 1;
    }
  }
  local_44 = 0;
  local_48 = *(undefined4 *)(local_14 + 0x6f0);
  local_40 = param_1 + 1;
  if (param_1 == 3) {
    local_40 = 5;
  }
  else if (param_1 == 4) {
    local_40 = 4;
  }
  puVar4 = &local_4c;
  puVar7 = FUN_00401170();
  FUN_00406d80(puVar7,(int)puVar4);
LAB_004125d2:
  local_8 = 0xffffffff;
  LOCK();
  piVar5 = (int *)(local_24 + -4);
  iVar6 = *piVar5;
  *piVar5 = *piVar5 + -1;
  UNLOCK();
  if (iVar6 == 1 || iVar6 + -1 < 0) {
    (**(code **)(**(int **)(local_24 + -0x10) + 4))((undefined4 *)(local_24 + -0x10),uVar3);
  }
  LOCK();
  piVar5 = (int *)(local_38 + -4);
  iVar6 = *piVar5;
  *piVar5 = *piVar5 + -1;
  UNLOCK();
  if (iVar6 == 1 || iVar6 + -1 < 0) {
    (**(code **)(**(int **)(local_38 + -0x10) + 4))((undefined4 *)(local_38 + -0x10));
  }
  ExceptionList = local_10;
  return;
}

