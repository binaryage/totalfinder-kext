# TotalFinder.kext

This source code implements kernel extension used by TotalFinder.

**TotalFinder** is a plugin for Apples's Finder.app which brings tabs, dual panels and more!

<img src="http://totalfinder.binaryage.com/shared/img/totalfinder-mainshot.png">

## How does .DS_Store redirection work?

I'm pretty excited about solving the problem which has been bugging me for more than two years since the day I switched to Macintosh. Every single day! 

Look, I use Finder.app with enabled hidden files and I'm also pretty heavy Terminal.app user. The .DS_Store litter makes me cry! If you ever happened to google for a solution, you could find just some simple scripts for deleting .DS_Store files (futile!). Or maybe there is some commercial app which is capable of watching filesystem and deleting them after creation. But this is not good enough for me! I'm using folder colors in Finder ;)

Here is what I did in TotalFinder:

* I've redirected low-level filesystem calls which Finder.app does: 
  * Anytime Finder.app is asking to open `/some/folder/.DS_Store` file, I open it as `/usr/local/.dscache/some/folder/_DS_Store`
  * This way Finder thinks files are at original places but they are being physically created in prefix folder, effectively sandboxing them
  * The only exception is the prefix folder itself, when you go and see it in the Finder, no redirection is applied
* I've implemented kernel extension Echelon, which monitors folder renames (and deletes) and sends them to TotalFinder
  * You see why. This is important to keep DS_Store folder structure in prefix directory mirroring actual structure on the disk

Yeah, kernel extension sounds scary. But I didn't find a better solution in user-space. FSEvents are not precious enough (it just reports "something was changed"). BSD kqueues must be registered on per-file basis, so it is not usable in this scenario. In the end of the day that kernel extension turned out to be really light-weight solution. I use KAUTH API to monitor kernel filesystem events. I do it only if TotalFinder is connected and only for renames and deletes. Testing is simple C-string comparison and sending notification via socket.

I'm using TotalFinder with this redirection enabled for a while and it works pretty well. I've noticed only one drawbacks so far:

* .DS_Store file is created when you modify Spotlight comment on a file
  This is caused by mdworker process and has no direct relation to Finder.app process. 
  It seems like Apple engineers scattered DS_Store functionality into more applications.
  I'm still investigating this. Temporary workaround is not using these Spotlight comments. Which is my case anyway.

## Visit [totalfinder.binaryage.com](http://totalfinder.binaryage.com)

#### License: [MIT-Style](totalfinder-kext/raw/master/license.txt)