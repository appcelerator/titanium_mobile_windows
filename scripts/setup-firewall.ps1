param (
    [string]$nodeVersion
)


ForEach($version in Get-Command node -Type Application)
{
    if ($version.Version -eq "$($nodeVersion).0")
    {
        $nodeInfo = $version
    }
}

Write-Host $nodeInfo
$nodeExe = $nodeInfo.Source
Write-Host "Node exe is " $nodeExe
Write-Host "Node version is " $nodeVersion

# Setup UDP

$ruleNameUDP= "Node $($nodeVersion) UDP"

$existingRuleUDP = Get-NetFirewallRule -DisplayName $ruleNameUDP -ErrorAction SilentlyContinue

if ($existingRuleUDP.length -ne 0)
{
    Write-Host "UDP rule exists, removing"
    Remove-NetFirewallRule -DisplayName $ruleNameUDP
}


Write-Host "Running New-NetFirewallRule with args -DisplayName $($ruleNameUDP) -Direction Inbound  -Protocol UDP -Action Allow -EdgeTraversalPolicy Allow -Program $($nodeExe)"
New-NetFirewallRule -DisplayName $ruleNameUDP -Direction Inbound  -Protocol UDP -Action Allow -EdgeTraversalPolicy Allow -Program $nodeExe

$ruleInfo = Get-NetFirewallRule -DisplayName $ruleNameUDP | Get-NetFirewallApplicationFilter
Write-Host $ruleInfo.Program
Write-Host

# Setup TCP

$ruleNameTCP = "Node $($nodeVersion) TCP"

$existingRuleTCP = Get-NetFirewallRule -DisplayName $ruleNameTCP -ErrorAction SilentlyContinue

if ($existingRuleTCP.length -ne 0)
{
    Write-Host "TCP rule exists, removing"
    Remove-NetFirewallRule -DisplayName $ruleNameTCP
}

Write-Host "Running New-NetFirewallRule with args -DisplayName $($ruleNameTCP) -Direction Inbound  -Protocol TCP -Action Allow -EdgeTraversalPolicy Allow -Program $($nodeExe)"
New-NetFirewallRule -DisplayName $ruleNameTCP -Direction Inbound  -Protocol TCP -Action Allow -EdgeTraversalPolicy Allow -Program $nodeExe

$ruleInfo = Get-NetFirewallRule -DisplayName $ruleNameTCP | Get-NetFirewallApplicationFilter
Write-Host $ruleInfo.Program