
void __fastcall FUN_0042b6b0(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  int iVar4;
  undefined4 *this;
  void *unaff_EBX;
  int unaff_ESI;
  void *unaff_EDI;
  char *pcVar5;
  int local_60;
  wchar_t *local_5c;
  char local_58 [9];
  undefined2 local_4f;
  char local_4d;
  undefined1 local_4c;
  undefined1 local_4b;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  undefined4 local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_005363f8;
  local_10 = ExceptionList;
  uVar1 = DAT_0055f00c ^ (uint)&stack0xfffffffc;
  ExceptionList = &local_10;
  local_14 = uVar1;
  piVar2 = (int *)FUN_00406b10();
  if (piVar2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  iVar3 = (**(code **)(*piVar2 + 0xc))();
  local_5c = (wchar_t *)(iVar3 + 0x10);
  local_8 = 0;
  FUN_004054f0(&stack0xffffff78,L"dpi_index");
  local_8._0_1_ = 1;
  iVar3 = *(int *)ThreadLocalStoragePointer;
  if (*(int *)(iVar3 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 2;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 1;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8._0_1_ = 0;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),uVar1,unaff_EDI);
  iVar4 = _wtoi(local_5c);
  piVar2 = (int *)FUN_00406b10();
  if (piVar2 == (int *)0x0) {
                    /* WARNING: Subroutine does not return */
    FUN_00406bc0(0x80004005);
  }
  local_60 = (**(code **)(*piVar2 + 0xc))();
  local_60 = local_60 + 0x10;
  local_8._0_1_ = 3;
  FUN_00406540(&local_60,0x54cb78);
  FUN_00405df0((int *)(local_60 + -0x10));
  local_8._0_1_ = 4;
  if (*(int *)(iVar3 + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 5;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 4;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8 = CONCAT31(local_8._1_3_,3);
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),unaff_ESI,unaff_EBX);
  iVar3 = _wtoi(local_5c);
  memset(local_58 + 1,0,0x40);
  local_58[8] = *(char *)(param_1 + 0x6f0) + -1;
  local_4c = (undefined1)iVar3;
  local_4d = (char)iVar4 + '\x01';
  pcVar5 = local_58;
  local_58[0] = '\0';
  local_58[1] = 'U';
  local_58[2] = '\"';
  local_58[3] = -0x52;
  local_58[4] = '\t';
  local_58[5] = '\x03';
  local_58[6] = '\0';
  local_58[7] = '\0';
  local_4f = 0;
  local_4b = (undefined1)((uint)iVar3 >> 8);
  this = FUN_00401200();
  FUN_0043be10(this,pcVar5);
  FUN_00405430(&local_60);
  FUN_00405430((int *)&local_5c);
  ExceptionList = local_10;
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

