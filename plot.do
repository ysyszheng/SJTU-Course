cd "/home/vincent/Documents/Obsidian Vault/Econometrics/data/"
use "./main.dta", clear

bysort year: egen comp_med = mean(comp)
bysort year: egen comp_owner_med = mean(comp) if belong==1
bysort year: egen comp_renter_med = mean(comp) if belong==0
bysort year: egen hp_med = mean(hp) if belong==1

twoway connected comp_med year, lpattern(1) || connected comp_owner_med year, lpattern(-) ||  connected comp_renter_med year, lpattern(_._) xtitle("year") ytitle("Mean Consumption / RMB") legend(label(1 "all") label(2 "houseowner") label(3 "renter"))
twoway connected hp_med year, lpattern(1) xtitle("year") ytitle("Mean Housing Prices / RMB") legend(label(1 "housing prices"))

twoway scatter lcomp lhp, msize(2pt) || lfit lcomp lhp, lwidth(1.5pt) by(belong year, row(2)) xtitle("Log(Housing Prices)") ytitle("Log(Consumption)") legend(label(1 "Log(Consumption)") label(2 "fit") size(vsmall)) yscale(r(5 15))