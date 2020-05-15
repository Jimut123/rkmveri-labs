if [ $1 -eq 1 ]
then
	python mask_rcnn.py --mask-rcnn mask-rcnn-coco --image images/example_01.jpg --visualize 1
 
elif [ $1 -eq 2 ]
then
	python mask_rcnn.py --mask-rcnn mask-rcnn-coco --image images/example_02.jpg --visualize 1
 
elif [ $1 -eq 3 ]
then
	python mask_rcnn.py --mask-rcnn mask-rcnn-coco --image images/example_03.jpg --visualize 1
else
    echo "Not OK"
fi
