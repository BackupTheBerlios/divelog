#!/usr/bin/perl 
# Copyright 2002 Markus Grunwald 
# All other Copyrights (especially Qt and mysql) belong to their owners 

#*************************************************************************
#This file is part of divelog.
#
#divelog is free software; you can redistribute it and/or modify
#it under the terms of the GNU General Public License as published by
#the Free Software Foundation; either version 2 of the License, or
#(at your option) any later version.
#
#divelog is distributed in the hope that it will be useful,
#but WITHOUT ANY WARRANTY; without even the implied warranty of
#MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#GNU General Public License for more details.
#
#You should have received a copy of the GNU General Public License
#along with divelog; if not, write to the Free Software
#Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
#**************************************************************************/

#******************************************************************************
# Filename : eoncsvimport.pl                                                  *
# CVS Id   : $Id: eoncsvimport.pl,v 1.1 2002/06/02 09:59:52 grunwalm Exp $     *
# --------------------------------------------------------------------------- *
# Files subject    :                                                          *
# Owner            : Markus Grunwald (MG)                                     *
# Date of Creation :                                                          *
# --------------------------------------------------------------------------- *
# To Do List :                                                                *
# --------------------------------------------------------------------------- *
# Notes :                                                                     *
#******************************************************************************/

#use strict;
use DBI();

my $csvname = shift;

# Connect to the database.
my $dbh = DBI->connect("DBI:mysql:database=divelog-test;host=zaphod",
                       "markus", "ArPPCa", {'RaiseError' => 1});

open  MAIN,    "$csvname.csv"      or die "can't open $csvname.csv : $!";
open  PROFILE, "$cvsname\$pro.csv" or die "can't open $cvsname\$pro.csv: $!";
#open  NOTES,   "$cvsname\$not.csv" or die "can't open $cvsname\$pro.csv: $!";
#open  PROFILE, "$cvsname\$dge.csv" or die "can't open $cvsname\$pro.csv: $!";

while (<MAIN>){
    ($RecordID,$DiveNumber,$Date,$TimeIn,$RSeries,$DCDiveNo,$DivTimeSec,$SurfIntSec,
     $MaxDepth,$AvgDepth,$SerialNo,$PersData,$DCType,$SampleRate,$AltitudeMode,
     $SolTimeAdj,$Modified,$Location,$Site,$Weather,$WaterVis,$AirTemp,$WaterTemp,
     $Partner,$DiveMaster,$BoatName,$CylDesc,$CylSize,$CylUnits,$CylWrkPres,
     $CylStrtPres,$CylEndPres,$SACRate,$SACUnits,$Custom1,$Custom2,$Custom3,
     $Custom4,$WeightUsed,$OxygenPct,$OLFPct,$OTUFlag)=split(/,/);
    
    #Strip " "
    ($Date) = ( $Date=~ /"([^"]*)"/ );
    ($TimeIn) = ( $TimeIn=~ /"([^"]*)"/ );
    ($PersData) = ( $PersData=~ /"([^"]*)"/ );
    ($Location) = ( $Location=~ /"([^"]*)"/ );
    ($Site) = ( $Site =~ /"([^"]*)"/ );
    ($WaterVis) = ( $WaterVis=~ /"([^"]*)"/ );
    ($Weather) = ( $Weather=~ /"([^"]*)"/ );
    ($Partner) = ( $Partner=~ /"([^"]*)"/ );
    ($DiveMaster) = ( $DiveMaster=~ /"([^"]*)"/ );
    ($BoatName) = ( $BoatName=~ /"([^"]*)"/ );
    ($CylDesc) = ( $CylDesc=~ /"([^"]*)"/ );
 
    
    ($d1,$d2,$d3)= ( $SerialNo =~ /(..)(..)(..)/);
                             
    #First, look up whether the divecomputer exists
    my $sth = $dbh->prepare("SELECT * FROM divecomputer where serial_number=\"$d1.$d2.$d3\"");
    if (!$sth) {
        die "Error:" . $dbh->errstr . "\n";
    }
    if (!$sth->execute) {
        die "Error:" . $sth->errstr . "\n";
    }
    if ($sth->rows != 1)
    {
        die "Multiple entries for divecomputer with serial_number $d1.$d2.$d3\nThe database is corrupt.";
    }
    my $row = $sth->fetchrow_hashref();
    #    print "Found a row: snr = $row->{'serial_number'}, diver_number=$row->{'diver_number'}, name = $row->{'name'}\n";
    $sth->finish();
    
    ($year,$month,$day) = ( $Date   =~ /(....)(..)(..)/ );
    ($hour,$minute)     = ( $TimeIn =~ /(..)(..)/ );
    
    #Convert dive length to h:m:s
    
    $len_h=int($DivTimeSec/3600);
    $len_m=int(( $DivTimeSec%3600 )/60);
    $len_s=$DivTimeSec-$len_h*3600-$len_m*60;
    
    
    $sql_statement="insert into dive ( number, date, sync, diver_number, place, location, surface_intervall, "
             . "altitude_mode, water_temperature, start_pressure, "
             . "end_pressure, max_depth, length, profile ) values ( "
             . $DiveNumber .", "
             . "\"$year-$month-$day $hour:$minute:00\", "
             . "1, "
             . $row->{'diver_number'} . ", "
             . "\"$Location\", "
             . "\"$Site\", "
             . $SurfIntSec . ", "
             . ($AltitudeMode+1)*700 . ", "
             . $WaterTemp . ", "
             . $CylStrtPres . ", "
             . $CylEndPres . ", "
             . $MaxDepth . ", "
             . "\"". sprintf( "%u:%02u:%02u", $len_h, $len_m,  $len_s ) . "\", "
             . "NULL" . ")" ;
    print $sql_statement . "\n";
    $dbh->do($sql_statement) ;
    
}

# Disconnect from the database.
$dbh->disconnect();

