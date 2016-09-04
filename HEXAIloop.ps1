$ScriptBlockA = {
    param($dir)
    cd $dir
    .\HEXAI.exe 15 6 8 8 4 4 4
    gc bestUnits.txt | select -First 2 | Out-File ..\rivals.txt -Append -Encoding ascii
}

$ScriptBlockB = {
    param($dir)
    cd $dir
    cp ..\rivals.txt .
    cp ..\rivals.txt startingRivals.txt
    sleep -s 15
    rm ..\rivals.txt -ErrorAction SilentlyContinue
    .\HEXAI.exe 35 6 8 8 3 10 2
    gc bestUnits.txt | select -First 2 | Out-File ..\rivals.txt -Append -Encoding ascii
}
$dirs = gci | where {$_.mode -like 'd*'}
if($dirs) {
    $j = $i = [int]($dirs | select -last 1).name + 1
}
else {
    $j = $i = 1
}

while ($true) {
    $j += 3
    for ($i; $i -lt $j; $i++) {
        mkdir $i
        cp .\HEXAI.exe $i
        if($i -le 3) {
            $i
            Start-Job $ScriptBlockA -ArgumentList "$PSScriptRoot\$i"
        }
        else {
            Start-Job $ScriptBlockB -ArgumentList "$PSScriptRoot\$i"
        }
        sleep -s 1
    }
    While (Get-Job -State 'Running')
    {
        Get-Job -State 'Running' | Format-Table
        sleep -s 120
    }
    Get-Job | Remove-Job -force
}

