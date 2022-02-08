$libFolder = "$PSScriptRoot/lib" 
$execFolder = "$PSScriptRoot/exec"

$libs = Get-ChildItem $libFolder | 
       Where-Object {$_.PSIsContainer} | 
       Foreach-Object {$_}

$projs = Get-ChildItem $execFolder | 
       Where-Object {$_.PSIsContainer} | 
       Foreach-Object {$_.FullName}

Foreach ($proj in $projs) {
    # Here we have an arduino project
    if (Get-ChildItem -Name "*.ino" -Path $proj) {
        # Create src dir
        if (Test-Path -Path "$proj/src") {
            Write-Host "src/ already exists in $proj, skipping..."
            continue
        }
        New-Item -ItemType Directory -Path "$proj/src"

        Foreach ($lib in $libs) {
            New-Item -ItemType SymbolicLink -Path `
                "$proj/src/$($lib.Name)" -Target $lib.FullName
        }
    } elseif (Get-ChildItem -Name "meson.build" -Path $proj) {
        if (Test-Path -Path "$proj/subprojects") {
            Write-Host "subprojects/ already exists in $proj, skipping..."
            continue
        }
        New-Item -ItemType SymbolicLink -Path `
            "$proj/subprojects" -Target $libFolder
    }
}



