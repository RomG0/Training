$file1 = Read-Host -Prompt "Enter path to file 1"
$file1 = $file1 -replace '\"', ''
if (-not (Test-Path -Path $file1 -PathType Leaf)) {
    Write-Host "File doesn't exist!"
    break
}

$file2 = Read-Host -Prompt "Enter path to file 2"
$file2 = $file2 -replace '\"', ''
if (-not (Test-Path -Path $file2 -PathType Leaf)) {
    Write-Host "File doesn't exist!"
    break
}


If (Compare-Object (Get-Content $file1.Trim('"')) (Get-Content $file2.Trim('"'))) {
    Write-Host "Files are different"
} Else {
    Write-Host "Files are the same"
}