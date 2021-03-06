#! /bin/bash

# Copyright 2021 Bloomberg Finance L.P.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

DEFS_FILE=`/usr/bin/mktemp`
QS_FILE=`/usr/bin/mktemp`

ENCODED_VHOST=$4
if [ "$4" == "/" ];
then
    ENCODED_VHOST="%2f"
fi

SRC_PORT=15675
DST_PORT=15672
DST_AMQP_URI="amqp://"
SRC_AMQP_URI="amqp://guest:guest@rabbit4:5672/$ENCODED_VHOST"

if [ "$3" == "shared2" ];
then 
    SRC_PORT=15672
    DST_PORT=15675
    SRC_AMQP_URI="amqp://"
    DST_AMQP_URI="amqp://guest:guest@rabbit4:5672/$ENCODED_VHOST"
fi

SRC_FARM_URI="http://localhost:$SRC_PORT"
DST_FARM_URI="http://localhost:$DST_PORT"

RUNID="switch$RANDOM"

echo "Pausing vhost $4"
$1 $2 vhost pause $4
echo "Switching $4 to farm $3"
$1 $2 map farm $4 $3
echo "Disconnecting initial brokerside connections"
$1 $2 vhost backend_disconnect $4
sleep 2

echo "Retrieving existing vhost definitions"
curl -s -u guest:guest -H "content-type:application/json" -XGET $SRC_FARM_URI/api/definitions/$ENCODED_VHOST > $DEFS_FILE

echo "Exporting existing vhost defitions to new cluster $3"
curl -s -u guest:guest -H "content-type:application/json" -XPOST $DST_FARM_URI/api/definitions/$ENCODED_VHOST -d @$DEFS_FILE

echo "Shovelling queues to $3"
curl -s -u guest:guest -H "content-type:application/json" -XGET $SRC_FARM_URI/api/queues/$ENCODED_VHOST > $QS_FILE
node shovel_queues.js $QS_FILE $RUNID $SRC_AMQP_URI $DST_AMQP_URI $ENCODED_VHOST 15672
sleep 1

echo "Unpausing vhost $4"
$1 $2 vhost unpause $4
echo "Full disconnect for $4"
$1 $2 vhost force_disconnect $4

