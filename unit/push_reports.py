#!/usr/bin/env python

import os
import sys
import shlex
from datetime import *
from subprocess import *

# relative path to wiki directory holding test reports
WIKI_PATH='../../pummel.wiki/test_reports/'

# don't need date/time because that is logged in hg
LOG_SKELETON='''
## ## ## ## ## ## ## ## ## ## ##
##        FILL ME OUT         ##
## ## ## ## ## ## ## ## ## ## ##
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

            # append the coverage report
            cov = '_..##src##'+ test.replace('test_', '') +'.cpp.trucov'
            if os.path.isfile(cov):
                reports.append(cov)
            
            # write the report
            self.write_report(test, reports)
    

    def write_report(self, which, reports):
        wiki = WIKI_PATH + which +'.wiki'
        
        f = open(wiki, 'w+')
        
        for report in reports:
            ftmp = open(report, 'r')
            content = ftmp.read()
            ftmp.close()
            
            f.write(content+ '\n\n')

        f.close()

    
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
        
        for std in p.communicate():
            print(std)


    def default_logs(self):
        for test in self.tests:
            name = test +'_log.txt'
            
            if not os.path.isfile(name):
                f = open(name, 'w+')
                f.write(LOG_SKELETON)
                f.close()


## ## ## ## ## ## ## ## ## ## ##
##          EXECUTE           ##
## ## ## ## ## ## ## ## ## ## ##
if __name__ == '__main__':
    monkey = Pummel_report()
    
    for test in sys.argv:
        monkey.append_report(test)
        
    monkey.default_logs()
    
    if not '--log_only' in sys.argv:
        monkey.build_reports()
        monkey.push_reports()
