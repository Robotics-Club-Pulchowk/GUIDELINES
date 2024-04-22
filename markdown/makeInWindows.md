# MAKE IN WINDOWS

We use `MINGW` for GCC in `Windows` computer. MINGW comes with its own `mingw32-make` command. 

```powershell
mingw32-make --version
```

If you have set the environment variables properly, the command will be executed successfully.

But still, we prefer `make` command. So we rename `mingw32-make` to `make`.
-  Go to `C:/mingw/bin`.
-  Make another copy of `mingw32-make.exe`.
-  Rename it to `make.exe`.
  
Now you can try `make` command.
```powershell
make --version
```