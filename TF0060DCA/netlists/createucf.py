import sys,re

ucfheader = """# Copyright (C) 2016-2022, Stephen J. Leary
# All rights reserved.
#
# This file is part of TF4060 (Terrible Fire 060 Accelerator)
#
# TF4060 is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# TF4060 is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with TF4060. If not, see <http://www.gnu.org/licenses/>.

"""

ucftimespec = """
TIMESPEC "TS_P2P" = FROM "PADS" TO "PADS" 10 ns;

"""

if len(sys.argv) != 2:
        print "Usage: %s <netlist>" % (sys.argv[0])
        sys.exit(-1)

fname = sys.argv[1]

currentNet = None

cplds = ["CPLD"]
ucfs = {}
ucfclocks = {}

exclude = ["GND","VCC33","VCC12","TCK","TDO","TMS","TDINT","TDI"]
busre = re.compile(r'(\d+$)')
notbus = ["AS20", "DS20", "RW20", "BR20", "BG20",
          "INT2", "EXT90",
          "AVEC60", "BB60", "BG60", "BR60"] 

clocks = ['SCLK', 'CLKOUT']

with open(fname) as f:
        content = f.readlines()
        for line in content:
                tokens = (line).split()
                if len(tokens) == 0:
                        continue
                print len(tokens)
                if len(tokens) == 3:
                        currentNet = tokens[0].replace("/","")
                        tokens = tokens[1:]
                if len(tokens) == 5:
                        currentNet = tokens[0].replace("/","")
                        tokens = tokens[1:]
                print tokens
                if (currentNet is not None) and not currentNet in exclude:

                        chip = tokens[0]
                        print chip
                        if chip in cplds:
                                ucf = ucfs.get(chip, '')
                                if currentNet in notbus:
                                        netname = currentNet
                                else:
                                        netname = busre.sub(r'<\1>', currentNet)

                                netname = netname.replace('_<', '<')
                                        
                                newucf = 'NET "%s"      LOC="%s";\n' % (netname,tokens[1])

                                if not currentNet in clocks:
                                        ucf += newucf 
                                        ucfs[chip] = ucf
                                else:
                                        ucf = ucfclocks.get(chip, '')
                                        ucf += newucf
                                        ucf += 'NET "%s" BUFG=CLK;\n' % (netname,)
                                        ucf += 'NET "%s" TNM_NET = "%s"; # gives the net clk a group name as %s\n\n' % (netname, netname, netname)
                                        ucfclocks[chip] = ucf
                                        

for ucfkey in ucfs.keys():
        f = open(ucfkey+".ucf","w")
        f.write(ucfheader)
        f.write(ucfclocks[ucfkey])
        f.write(ucftimespec)
        f.write(ucfs[ucfkey])
        f.close()
        
