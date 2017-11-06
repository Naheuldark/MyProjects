# include "../../include/keyframes/KeyframeCollection.hpp"
# include <glm/gtx/compatibility.hpp>

# include <glm/gtc/quaternion.hpp>

void KeyframeCollection::add(float time, const GeometricTransformation& transformation)
{
    m_keyframes.insert(std::make_pair(time, transformation));
}

glm::mat4 KeyframeCollection::interpolateTransformation(float time) const
{
    //TODO: Complete the interpolation framework
    if (!m_keyframes.empty()) {
        //Handle the case where the time parameter is outside the keyframes time scope.
        std::map<float, GeometricTransformation>::const_iterator itFirstFrame = m_keyframes.begin();
        std::map<float, GeometricTransformation>::const_reverse_iterator itLastFrame = m_keyframes.rbegin();
        if (time <= itFirstFrame->first)
            return itFirstFrame->second.toMatrix();
        if (time >= itLastFrame->first)
            return itLastFrame->second.toMatrix();

        //Get keyframes surrounding the time parameter
        std::array<Keyframe, 2> result = getBoundingKeyframes(time);
        float time0 = result[0].first;
        float time1 = result[1].first;
        GeometricTransformation transform0 = result[0].second;
        GeometricTransformation transform1 = result[1].second;

        GeometricTransformation transform;
        float time_factor = (time-time0)/(time1-time0);
        transform.setOrientation(glm::slerp(transform0.getOrientation(), transform1.getOrientation(), time_factor));
        transform.setTranslation(transform0.getTranslation() * (1 - time_factor) + transform1.getTranslation() * time_factor);
        transform.setScale(transform0.getScale() * (1 - time_factor) + transform1.getScale() * time_factor);

        return transform.toMatrix();
    
    } else {
        return glm::mat4(1.0);
    }
}

bool KeyframeCollection::empty() const
{
    return m_keyframes.empty();
}

std::array< KeyframeCollection::Keyframe, 2 > KeyframeCollection::getBoundingKeyframes(float time) const
{
    std::array<KeyframeCollection::Keyframe, 2> result {
        std::make_pair(0, GeometricTransformation()),
        std::make_pair(0, GeometricTransformation()) };
    std::map<float, GeometricTransformation>::const_iterator upper = m_keyframes.upper_bound(time);
    std::map<float, GeometricTransformation>::const_iterator lower = std::prev(upper);
    std::map<float, GeometricTransformation>::const_iterator end = m_keyframes.end();
    if (upper != end && lower != end) {
        result[0] = *lower;
        result[1] = *upper;
    }
    return result;
}
