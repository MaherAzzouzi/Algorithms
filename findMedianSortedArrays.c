

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size){

    int i=0, j=0, k=0;
    
    double nums12_merged[10000];
    
    
    while(i<nums1Size && j<nums2Size)
    {
        
        if(nums1[i] > nums2[j])
            nums12_merged[k++] = nums2[j++];
        else
            nums12_merged[k++] = nums1[i++];
        
    }
    
    for(;j<nums2Size;j++)
        nums12_merged[k++] = nums2[j];
    for(;i<nums1Size;i++)
        nums12_merged[k++] = nums1[i];
    
    
    i = 0;
    k = --k;
    
    while(i<k)
    {
        i++;
        k--;       
    }
    
    if(i == k)
        return nums12_merged[i];
    else
        return (nums12_merged[i]+nums12_merged[k])/2;
}

