# Stworzenie sshconfig

## OUTPUT

Zamiast

```bash
ssh user@host
```

```bash
ssh host-alias
```

## INSTRUKCJA

```bash
cd ~/.ssh
vi config  # jesli nie ma tego pliku to touch config i potem ten step
```

> ~/.ssh/config:

```bash
Host diablo
    HostName <targetowy host>
    User <twoj uzytkownik>
```

## SOURCE

[https://stackoverflow.com/questions/56287059/how-to-set-up-an-ssh-config-file-for-beginners](https://stackoverflow.com/questions/56287059/how-to-set-up-an-ssh-config-file-for-beginners)
