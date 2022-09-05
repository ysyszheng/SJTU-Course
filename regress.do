cd "/home/vincent/Documents/Obsidian Vault/Econometrics/data/"
use "./main.dta", clear

xtset fid year
// household-level

// Owner
xtreg lcomp lhp linc i.year if belong==1, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year if belong==1, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year lgdp unemp if belong==1, fe

// Renter
xtreg lcomp lhp linc i.year if belong==0, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year if belong==0, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year lgdp unemp if belong==0, fe

xtreg lcomp lhp linc i.year, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year, fe
xtreg lcomp lhp linc lsize lsave lmort ldebt num i.year lgdp unemp, fe

// provincal level

// Owner
xtreg lcomp lhpm linc i.year if belong==1, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year if belong==1, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year lgdp unemp if belong==1, fe

// Renter
xtreg lcomp lhpm linc i.year if belong==0, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year if belong==0, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year lgdp unemp if belong==0, fe

xtreg lcomp lhpm linc i.year, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year, fe
xtreg lcomp lhpm linc lsize lsave lmort ldebt num i.year lgdp unemp, fe