#!/usr/bin/env python

import os
import sys
import shlex
from datetime import *
from subprocess import *

# relative path to wiki directory holding test reports
WIKI_PATH='../../pummel.wiki/test_reports/'

REPORT_DELIM='''## ## ## ## ## ## ## ## ## ## ##
##         SECTION          ##
## ## ## ## ## ## ## ## ## ## ##\n
'''

class Pummel_report:
    
    def __init__(self):
        self.tests = []
        self.reports = []
        
    def append_report(self, test):
        header = './tests/'+ test +'.h'
        
        if (os.path.isfile(test) and test.startswith('test_')) and os.path.isfile(header):
            self.tests.append(test)
    
    
    def build_reports(self):
        for test in self.tests:
            reports = []
            
            # append the log
            log = test +'_log.txt'
            if os.path.isfile(log):
                reports.append(log)

            # append the unit tests
            ut = test +'_ut.txt'
            if os.path.isfile(ut):
                reports.append(ut)

            # append the coverage report
            cov = '_..##src##'+ test.replace('test_', '') +'.cpp.trucov'
            if os.path.isfile(cov):
                reports.append(cov)
            
            # write the report
            self.write_report(test, reports)
    

    def write_report(self, which, reports):
        wiki = WIKI_PATH + which +'.wiki'
        
        f = open(wiki, 'w+')
        
        # write revision number of the project
        f.write(REPORT_DELIM.replace('SECTION', 'REVISION '))
        
        cmd = shlex.split('hg log -l1 ./tests/'+ which +'.h')
        p = Popen(cmd, stdin=PIPE, stderr=PIPE, stdout=PIPE)
        std = p.communicate()
        
        f.write(std[0] +'\n\n')
                
        #try:
        # write misc. commends
        f.write(REPORT_DELIM.replace('SECTION', 'COMMENTS '))
        f.write(self.write_file(reports[0]))
        #except:
        #    pass
        
        try:
            # write unit test results
            f.write(REPORT_DELIM.replace('SECTION', 'UNIT TEST'))
            f.write(self.write_file(reports[1]))
        except:
            pass
        
        try:
            # write coverage reports
            f.write(REPORT_DELIM.replace('SECTION', 'COVERAGE '))
            f.write(self.write_file(reports[2]))
        except:
            pass
        
        f.close()

        
    def write_file(self, filename):
        ftmp = open(filename, 'r')
        content = ftmp.read()
        ftmp.close()
        
        return content+ '\n\n'

    
    def push_reports(self):
        os.chdir(WIKI_PATH)
        
        # get up to date
        self.hg_cmd('pull')
        self.hg_cmd('update')
        
        # add new files
        self.hg_cmd('add')
        
        commit_msg = '"pushing test reports for: '
        for test in self.tests:
            commit_msg += test +' '
        commit_msg += '"'

        # commit adds/overwrites
        self.hg_cmd("commit -m '"+ commit_msg +"'")
        
        # push changes
        # so far not able to sync popen user input with hg user input
        os.system('hg push https://code.google.com/p/pummel.wiki/')
        

    def hg_cmd(self, cmd):
        cmd = shlex.split('hg '+ cmd)
        
        p = Popen(cmd, stdin=PIPE, stderr=PIPE, stdout=PIPE)
        
        (stderr, stdout) = p.communicate()
        
        print stdout
        print stderr
        
        return (stderr, stdout)


## ## ## ## ## ## ## ## ## ## ##
##          EXECUTE           ##
## ## ## ## ## ## ## ## ## ## ##
if __name__ == '__main__':
    monkey = Pummel_report()
    
    for test in sys.argv:
        monkey.append_report(test)
        
    monkey.build_reports()
    monkey.push_reports()
