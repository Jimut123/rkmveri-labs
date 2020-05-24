if [ $1 -eq 1 ]
then
	python orig_mask_rcnn.py --input "./images/example_01.jpg" --model "mask-rcnn-coco/frozen_inference_graph.pb" --config "mask-rcnn-coco/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"
 
elif [ $1 -eq 2 ]
then
	python orig_mask_rcnn.py --input "./images/example_02.jpg" --model "mask-rcnn-coco/frozen_inference_graph.pb" --config "mask-rcnn-coco/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"
 
elif [ $1 -eq 3 ]
then
	python orig_mask_rcnn.py --input "./images/example_03.jpg" --model "mask-rcnn-coco/frozen_inference_graph.pb" --config "mask-rcnn-coco/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"
elif [ $1 -eq 4 ]
then
	python orig_mask_rcnn.py --input "./images/veri.jpg" --model "mask-rcnn-coco/frozen_inference_graph.pb" --config "mask-rcnn-coco/mask_rcnn_inception_v2_coco_2018_01_28.pbtxt"
	#python mask_rcnn.py --mask-rcnn mask-rcnn-coco --image images/veri.jpg --visualize 1
else
    echo "Not OK"
fi
