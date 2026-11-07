
void __fastcall FUN_0042b8d0(int param_1)

{
  uint uVar1;
  int *piVar2;
  int iVar3;
  undefined4 *this;
  void *unaff_ESI;
  char *pcVar4;
  wchar_t *local_5c;
  char local_58 [9];
  undefined2 local_4f;
  undefined1 local_4d;
  uint local_14;
  void *local_10;
  undefined1 *puStack_c;
  int local_8;
  
  local_8 = 0xffffffff;
  puStack_c = &LAB_0053555c;
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
  FUN_004054f0(&stack0xffffff8c,L"report_rate");
  local_8._0_1_ = 1;
  if (*(int *)(*(int *)ThreadLocalStoragePointer + 4) < DAT_0056ef90) {
    FUN_00448660(&DAT_0056ef90);
    if (DAT_0056ef90 == -1) {
      local_8._0_1_ = 2;
      FUN_00401290();
      _atexit(thunk_FUN_004013b0);
      local_8._0_1_ = 1;
      FUN_00448621(&DAT_0056ef90);
    }
  }
  local_8 = (uint)local_8._1_3_ << 8;
  FUN_00401a10(&DAT_0056ef20,*(int *)(param_1 + 0x6f0),uVar1,unaff_ESI);
  iVar3 = _wtoi(local_5c);
  memset(local_58 + 1,0,0x40);
  local_58[8] = *(char *)(param_1 + 0x6f0) + -1;
  local_58[0] = '\0';
  local_58[1] = 'U';
  local_58[2] = '#';
  local_58[3] = -0x52;
  pcVar4 = local_58;
  local_58[4] = '\n';
  local_58[5] = '\x03';
  local_58[6] = '\0';
  local_58[7] = '\0';
  local_4f = 0;
  local_4d = (undefined1)iVar3;
  this = FUN_00401200();
  FUN_0043be10(this,pcVar4);
  FUN_00405430((int *)&local_5c);
  ExceptionList = local_10;
  local_5c = L"\xe58b썝쳌譕櫬棿昁Sꅤ";
  __security_check_cookie(local_14 ^ (uint)&stack0xfffffffc);
  return;
}

