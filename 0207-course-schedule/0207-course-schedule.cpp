class Solution {
public:
    bool iscycle(int src,vector<bool> &vis,vector<bool> &recpath,vector<vector<int>>&edges){
        vis[src]=true;
        recpath[src]=true;
        for(int i =0;i<edges.size();i++){
            int v=edges[i][0];
            int u=edges[i][1];
            if(u==src){
                if(!vis[v]){
                    if(iscycle(v,vis,recpath,edges)){
                        return true;
                    }
                }else if(recpath[v]==true){
                    return true;
                }
            }
        }
        recpath[src]=false;
        return false;
    }
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        int n =numCourses;
        vector<bool> vis(n,false);
        vector<bool>recpath(n,false);
        for(int i =0;i<n;i++){
            if(!vis[i]){
                if(iscycle(i,vis,recpath,prerequisites)){
                    return false;
                }
            }
        }
        return true;
    }
};